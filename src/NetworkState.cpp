////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "protocol.hpp"
#include "AssetsDeclarations.hpp"
#include "AssetManager.hpp"
#include "GameStateManager.hpp"
#include "GameContext.hpp"
#include "NetworkState.hpp"

#include <iostream>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/System/Vector2.hpp>


////////////////////////////////////////////////////////////
NetworkState::NetworkState(GameContext* context) :
  GameState(context),
  _backToMenu(_context->fontManager, "Retour au menu"),
  _retryTimer(sf::Time::Zero),
  _retryCount(0),
  _connected(false),
  _plateauD(_context->textureManager),
  _sendingAllowed(false)
{
  _backToMenu.setPosition(sf::Vector2f(50,50));
  _backToMenu.setCallback([this](){
    switchToMenuState();
  });

  _statusText.setFont(_context->fontManager->get(Fonts::Arial));
  _statusText.setCharacterSize(20);
  _statusText.setString("En attente ...");
}


////////////////////////////////////////////////////////////
NetworkState::~NetworkState()
{
  
}


////////////////////////////////////////////////////////////
void NetworkState::prepare()
{
  if (_socket.connect(_context->ip, _context->port) != sf::Socket::Done)
  {
    std::cerr << "Impossible de se connecter !" << std::endl;
    return;
  }

  _socket.setBlocking(false);
  _connected = true;
}


////////////////////////////////////////////////////////////
void NetworkState::update(sf::Time dt)
{
  // Logique du jeu (Anim etc.. ?)
  
  // Logique réseau
  if (_connected)
  {
    sf::Packet packet;
    sf::Socket::Status status = _socket.receive(packet);
    
    if (status == sf::Socket::Done)
    {
      _timeoutTimer = sf::seconds(0);

      sf::Int32 packetType;
      if (packet >> packetType)
	handlePacket(packetType, packet);
    }
    else if (status == sf::Socket::Disconnected)
    {
      std::cout << "Déconnexion du serveur" << std::endl;
      switchToMenuState();
    }
    else
    {
      if (_timeoutTimer >= sf::seconds(5.f))
      {
	std::cout << "Timeout / Pas de données reçu du serveur " << std::endl;
	switchToMenuState();
      }
      
      _timeoutTimer += dt;
    }

    return;
  }

  // Tentative de reconnection
  // _retryTimer += dt;

  // if (_retryTimer >= sf::seconds(1.f)) // TODO: Intervalle à redéfinir
  // {
  //   _retryTimer = sf::Time::Zero;
  //   _retryCount++;
   
  //   if (_retryCount == 5)
  //   {
  //     switchToMenuState();
  //     return;
  //   }

  //   prepare();
  // }
}


////////////////////////////////////////////////////////////
void NetworkState::handleEvent(sf::Event& event)
{
  _backToMenu.catchEvent(event);
  _plateauD.catchEvent(event);
  
}


////////////////////////////////////////////////////////////
void NetworkState::draw()
{
  sf::RenderWindow* window = _context->window;
  window->draw(_backToMenu);
  window->draw(_statusText);
  window->draw(_plateauD);
}


////////////////////////////////////////////////////////////
void NetworkState::switchToMenuState()
{
  _socket.disconnect();
  _timeoutTimer = sf::seconds(0);
  
  GameStateManager* stateManager = _context->stateManager;
  stateManager->setState(State::Menu);
}


////////////////////////////////////////////////////////////
void NetworkState::handlePacket(sf::Int32 packetType, sf::Packet& packet)
{
  switch (packetType)
  {
  case ServerPacket::NameRequest:
  {
    sf::Packet pkt;
    pkt << _context->clientName;

    if (_socket.send(pkt) != sf::Socket::Done)
    {
      std::cerr << "Connexion perdu avec le serveur" << std::endl;
      switchToMenuState();
      return;
    }
    
  } break;


  case ServerPacket::BroadcastMessage:
  {
    std::string msg;
    if (!(packet >> msg))
    {
      std::cerr << "Impossible de décoder un message du serveur !" << std::endl;
      switchToMenuState();
      return;
    }

    _statusText.setString(msg);
  } break;

  case ServerPacket::CombinaisonRequest:
  {
    _statusText.setString("Veuillez choisir une combinaison");
    _sendingAllowed = true;
  } break;

  case ServerPacket::TurnNotFinished:
  {
    
  } break;

  case ServerPacket::TurnFinished:
  {
    
  } break;
  
  case ServerPacket::GameFinished:
  {
    
  } break;
  
  }
}

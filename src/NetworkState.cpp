////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "protocol.hpp"
#include "AssetsDeclarations.hpp"
#include "AssetManager.hpp"
#include "GameStateManager.hpp"
#include "GameContext.hpp"
#include "MusicPlayer.hpp"
#include "NetworkState.hpp"

#include <iostream>
#include <sstream>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/System/Vector2.hpp>


////////////////////////////////////////////////////////////
NetworkState::NetworkState(GameContext* context) :
  GameState(context),
  _backToMenu(_context->fontManager, "Retour au menu"),
  _retryTimer(sf::Time::Zero),
  _retryCount(0),
  _connected(false),
  _sendingAllowed(false),
  _statusText("En attente...", _context->fontManager->get(Fonts::Arial), 20),
  _validateButton(_context->fontManager, "Validate"),
  _board(_context->textureManager,_context->fontManager),
  _clientText("", _context->fontManager->get(Fonts::Arial), 20),
  _opponentText("", _context->fontManager->get(Fonts::Arial), 20)
{
  _backToMenu.setPosition(sf::Vector2f(50, 50));
  _backToMenu.setCallback([this](){
    switchToMenuState();
  });
  
  _validateButton.setPosition(sf::Vector2f(690, 630));
  _validateButton.setCallback([this]() {
      if (!_sendingAllowed)
      {
	std::cout << "Fonctionnalité non disponible pour le moment !"
		  << std::endl;
	return;
      }

      // Récupération de la combinaison du plateau
      if(!_board.validateCombi())
      {
	std::cerr << "Combinaison incorrecte !" << std::endl;
	return;
      }
      
      std::string combiStr = _board.getValidatedCombi();
      
      // Envoi de la combinaison
      sf::Packet packet;
      packet << combiStr;

      if (_socket.send(packet) != sf::Socket::Done)
      {
	_connected = false;
	std::cerr << "Impossible d'envoyer la combinaison au serveur ! Déconnexion..."
		  << std::endl;
      }
      
      _sendingAllowed = false;
  });

  _clientText.setPosition(sf::Vector2f(0, 100));
  _opponentText.setPosition(sf::Vector2f(0, 120));
}


////////////////////////////////////////////////////////////
NetworkState::~NetworkState()
{
  
}


////////////////////////////////////////////////////////////
void NetworkState::init()
{
  _context->musicPlayer->play(Musics::InGame);
  _statusText.setString("En attente...");
  _connected      = false;
  _sendingAllowed = false;
  _clientScore    = 0;
  _opponentScore  = 0;
  _opponentName   = "?";

  refreshScores();
}


////////////////////////////////////////////////////////////
void NetworkState::prepare()
{
  
  if (_clientName.empty())
    _clientName = _context->clientName;
  
  _clientText.setString(_clientName + " (0 Points)");
  
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
      //switchToMenuState();
    }
    else
    {
      // if (_timeoutTimer >= sf::seconds(5.f)) TODO: Intervalle à définir
      // {
      // 	std::cout << "Timeout / Pas de données reçu du serveur " << std::endl;
      // 	switchToMenuState();
      // }
      
      // _timeoutTimer += dt;
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
  _validateButton.catchEvent(event);
  _board.catchEvent(event);
}


////////////////////////////////////////////////////////////
void NetworkState::draw()
{
  sf::RenderWindow* window = _context->window;

  window->draw(_backToMenu);
  window->draw(_board);
  window->draw(_validateButton);
  window->draw(_statusText);
  window->draw(_clientText);
  window->draw(_opponentText);
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

  case ServerPacket::GameBegin:
  {
    std::string msg;
    if (!(packet >> msg))
    {
      std::cerr << "Impossible de décoder un message du serveur !" << std::endl;
      switchToMenuState();
      return;
    }

    _opponentName = msg;
    _opponentText.setString(_opponentName + " (0 Points)");
    _statusText.setString("La partie va commencer !");
  } break;

  case ServerPacket::CombinaisonRequest:
  {
    _statusText.setString("Veuillez choisir une combinaison");
    _sendingAllowed = true;
  } break;

  case ServerPacket::TurnNotFinished:
  {
    std::string board;
    if (!(packet >> board))
    {
      std::cerr << "Impossible de recevoir le plateau" << std::endl;
      switchToMenuState();
      return;
    }

    _board.doBoard(board);
  } break;

  case ServerPacket::TurnFinished:
  {
    sf::Int32 clientScore;
    sf::Int32 opponentScore;

    if (!(packet >> clientScore))
    {
      std::cerr << "Impossible de recevoir le score depuis le serveur"
		<< std::endl;
      switchToMenuState();
      return;
    }

    if (!(packet >> opponentScore))
    {
      std::cerr << "Impossible de recevoir le score depuis le serveur"
		<< std::endl;
      switchToMenuState();
      return;
    }

    _clientScore   = clientScore;
    _opponentScore = opponentScore;
    
    refreshScores();
    _board.empty();
  } break;
  
  case ServerPacket::GameFinished:
  {
    std::string msg;
    if (!(packet >> msg))
    {
      std::cerr << "Impossible de décoder un message du serveur !" << std::endl;
      switchToMenuState();
      return;
    }

    _statusText.setString("Le gagnant est: " + msg);
  } break;
  
  }
}


////////////////////////////////////////////////////////////
void NetworkState::refreshScores()
{
  std::stringstream sstream;
  sstream << _clientName << " (" << _clientScore << " Points)";

  _clientText.setString(sstream.str());
  sstream.str("");
  sstream << _opponentName << " (" << _opponentScore << " Points)";
  _opponentText.setString(sstream.str());
}

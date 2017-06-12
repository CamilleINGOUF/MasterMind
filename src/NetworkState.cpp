////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "NetworkState.hpp"
#include "GameStateManager.hpp"
#include "GameContext.hpp"

#include <SFML/Network/IpAddress.hpp>


////////////////////////////////////////////////////////////
NetworkState::NetworkState(GameContext* context) :
  GameState(context)
{
  if (!_font.loadFromFile("../media/fonts/arial.ttf"))
    exit(-1);

  _backToMenu.setFont(_font);
  _backToMenu.setLabel("Retour au menu");
  _backToMenu.setPosition(sf::Vector2f(50,50));
  _backToMenu.setCallback([this]()
			  {
			    switchToMenuState();
			  });

  
  _pionD.setPion({rouge});
  _pionD.setPosition(sf::Vector2f(0,0));
  _pionD.setScale(sf::Vector2f(5,5));
  _backToMenu.setCallback([this](){
      switchToMenuState();
    });

  _socket.setBlocking(false);

  if(_socket.connect(_context->ip, _context->port) != sf::Socket::Done)
  {
    switchToMenuState();
  }
}


////////////////////////////////////////////////////////////
NetworkState::~NetworkState()
{
  
}


////////////////////////////////////////////////////////////
void NetworkState::update(sf::Time dt)
{
  sf::Packet packet;
  if (_socket.receive(packet) == sf::Socket::Done)
  {
    _timeoutTimer = sf::seconds(0);
    sf::Int32 packetType;
    if (packet >> packetType)
    {
      handlePacket(packetType, packet);
    }
  }

  // TODO: Changer le timer à 1 - 2 Minutes !!
  /*if (_timeoutTimer >= sf::Time(sf::seconds(10.f)))
  {
    switchToMenuState();
    return;
    }
    
    _timeoutTimer += dt;*/
}


////////////////////////////////////////////////////////////
void NetworkState::handleEvent(sf::Event& event)
{
  _backToMenu.catchEvent(event);
}


////////////////////////////////////////////////////////////
void NetworkState::draw()
{
  sf::RenderWindow* window = _context->window;
  window->draw(_backToMenu);
  window->draw(_pionD);
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
  case 0:
    break;
  }
}

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "GameStateManager.hpp"
#include "JoiningState.hpp"
#include "NetworkState.hpp"

#include <iostream>
#include <stdexcept>


////////////////////////////////////////////////////////////
JoiningState::JoiningState(GameContext* context) :
  GameState(context),
  _cancel(_context->fontManager, "Retour"),
  _joinGame(_context->fontManager, "Jouer"),
  _hostAddress(_context->fontManager, "IP:Port", 17),
  _nickname(_context->fontManager, "Pseudo", 20)
{
  _cancel.setPosition(sf::Vector2f(200,150));
  _cancel.setCallback([this]() {
      GameStateManager* stateManager = _context->stateManager;
      stateManager->setState(State::Menu);
  });

  //< Rejoindre la partie
  _joinGame.setPosition(sf::Vector2f(200,100));
  _joinGame.setCallback([this]() {
      if (!validInput())
	return;

      GameStateManager* stateManager = _context->stateManager;
      stateManager->setState(State::InGame);
      NetworkState* state = dynamic_cast<NetworkState*>(stateManager->getCurrentState());
      state->prepare();
    });

  
  _hostAddress.setPosition(sf::Vector2f(200,50));
  _nickname.setPosition(sf::Vector2f(200,0));
}


////////////////////////////////////////////////////////////
JoiningState::~JoiningState()
{
}


////////////////////////////////////////////////////////////
void JoiningState::init()
{
  _nickname.setText("Pseudo");
  _hostAddress.setText("IP:Port");
}


////////////////////////////////////////////////////////////
void JoiningState::update(sf::Time dt)
{
}


////////////////////////////////////////////////////////////
void JoiningState::handleEvent(sf::Event& event)
{  
  _nickname.catchEvent(event);
  _hostAddress.catchEvent(event);
  _cancel.catchEvent(event);
  _joinGame.catchEvent(event);
}


////////////////////////////////////////////////////////////
void JoiningState::draw()
{
  sf::RenderWindow* window = _context->window;
  
  window->draw(_hostAddress);
  window->draw(_nickname);
  window->draw(_cancel);
  window->draw(_joinGame); 
}


////////////////////////////////////////////////////////////
bool JoiningState::validInput()
{
  std::string ipPort  = _hostAddress.getText();
  std::string name    = _nickname.getText();
  std::string ip      = ipPort.substr(0, ipPort.find(':'));
  std::string portStr = ipPort.substr(ipPort.find(':') + 1);

  unsigned short port;

  if (name.empty() || ipPort.empty())
    return false;
  
  try
  {
    port = std::stoi(portStr);
  }
  catch (const std::invalid_argument& err)
  {
    std::cerr << err.what() << std::endl;
    return false;
  }
  catch (const std::out_of_range& err)
  {
    std::cerr << err.what() << std::endl;
    return false;
  }

  _context->ip         = ip;
  _context->port       = port;
  _context->clientName = name;

  return true;
}

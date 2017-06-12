////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "GameStateManager.hpp"
#include "JoiningState.hpp"

#include <iostream>
#include <stdexcept>


////////////////////////////////////////////////////////////
JoiningState::JoiningState(GameContext* context) :
  GameState(context)
{
  FontManager* fontManager = _context->fontManager;
  
  _cancel.setFont(fontManager->get(Fonts::Arial));
  _cancel.setLabel("Retour");
  _cancel.setPosition(sf::Vector2f(200,150));
  _cancel.setCallback([this]() {
      GameStateManager* stateManager = _context->stateManager;
      stateManager->setState(State::Menu);
  });

  //< Rejoindre la partie
  _joinGame.setFont(fontManager->get(Fonts::Arial));
  _joinGame.setLabel("Jouer");
  _joinGame.setPosition(sf::Vector2f(200,100));
  _joinGame.setCallback([this]() {
      if (!validInput())
	return;

      GameStateManager* stateManager = _context->stateManager;
      stateManager->setState(State::InGame);
    });

  //_addressHost
  _addressHost.setFont(fontManager->get(Fonts::Arial));
  _addressHost.setText("adresse:host");
  _addressHost.setPosition(sf::Vector2f(200,50));

  //_nickname
  _nickname.setFont(fontManager->get(Fonts::Arial));
  _nickname.setText("pseudo");
  _nickname.setPosition(sf::Vector2f(200,0));
}


////////////////////////////////////////////////////////////
JoiningState::~JoiningState()
{
}


////////////////////////////////////////////////////////////
void JoiningState::update(sf::Time dt)
{
}


////////////////////////////////////////////////////////////
void JoiningState::handleEvent(sf::Event& event)
{
  sf::RenderWindow* window = _context->window;
  
  _nickname.catchEvent(event, *window);
  _addressHost.catchEvent(event, *window);
  _cancel.catchEvent(event);
  _joinGame.catchEvent(event);
}


////////////////////////////////////////////////////////////
void JoiningState::draw()
{
  sf::RenderWindow* window = _context->window;
  
  window->draw(_addressHost);
  window->draw(_nickname);
  window->draw(_cancel);
  window->draw(_joinGame); 
}


////////////////////////////////////////////////////////////
bool JoiningState::validInput()
{

  std::string ip;
  std::string portStr;

  std::cout << "get text" << std::endl;
  std::string ipPort = _addressHost.getText();

  std::cout << "get text" << std::endl;
  std::string name = _nickname.getText();

  std::cout << "trouver l'ip" << std::endl;
  ip = ipPort.substr(0, ipPort.find(':'));
  std::cout << "Trouver le port" << std::endl;
  portStr = ipPort.substr(ipPort.find(':') + 1);

  unsigned short port;
  
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

  _context->ip        = ip;
  _context->port      = port;
  _context->clientName = name;

  return true;
}

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "GameContext.hpp"
#include "GameStateManager.hpp"
#include "MenuState.hpp"

#include <iostream>
#include <stdexcept>
#include <SFML/Graphics/Color.hpp>


////////////////////////////////////////////////////////////
MenuState::MenuState(GameContext* context) :
  GameState(context)
{
  FontManager* fontManager = _context->fontManager;
  fontManager->load(Fonts::Arial, "../media/fonts/arial.ttf");

  
  //< Quitter
  _quit.setFont(fontManager->get(Fonts::Arial));
  _quit.setLabel("Quitter");
  _quit.setPosition(sf::Vector2f(200,150));
  _quit.setCallback([]() {
      exit(0);
  });
  
  //< Rejoindre un serveur
  _joinServer.setFont(fontManager->get(Fonts::Arial));
  _joinServer.setLabel("Rejoindre");
  _joinServer.setPosition(sf::Vector2f(180,100));
  _joinServer.setCallback([this](){
      GameStateManager* stateManager = _context->stateManager;
      stateManager->setState(State::Joining);
  });
}


////////////////////////////////////////////////////////////
MenuState::~MenuState()
{
  
}


////////////////////////////////////////////////////////////
void MenuState::update(sf::Time dt)
{
}


////////////////////////////////////////////////////////////
void MenuState::handleEvent(sf::Event& event)
{
  _quit.catchEvent(event);
  _joinServer.catchEvent(event);
}


////////////////////////////////////////////////////////////
void MenuState::draw()
{
  sf::RenderWindow* window = _context->window;

  window->draw(_quit);
  window->draw(_joinServer);
}

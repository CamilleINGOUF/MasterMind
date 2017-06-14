////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "GameContext.hpp"
#include "GameStateManager.hpp"
#include "MenuState.hpp"
#include "MusicPlayer.hpp"

#include <iostream>
#include <stdexcept>
#include <SFML/Graphics/Color.hpp>


////////////////////////////////////////////////////////////
MenuState::MenuState(GameContext* context) :
  GameState(context),
  _quit(context->fontManager, "Retour"),
  _joinServer(context->fontManager, "Rejoindre")
{
  //< Quitter
  _quit.setPosition(sf::Vector2f(450,150));
  _quit.setCallback([]() {
      exit(0);
  });
  
  //< Rejoindre un serveur
  _joinServer.setPosition(sf::Vector2f(430,100));
  _joinServer.setCallback([this](){
      GameStateManager* stateManager = _context->stateManager;
      stateManager->setState(State::Joining);
  });

  _background.setTexture(_context->textureManager->get(Textures::BoardBackground));
}


////////////////////////////////////////////////////////////
MenuState::~MenuState()
{
  
}


////////////////////////////////////////////////////////////
void MenuState::init()
{
  _context->musicPlayer->play(Musics::Menu);  
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

  window->draw(_background);
  window->draw(_quit);
  window->draw(_joinServer);
}

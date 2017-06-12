////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "App.hpp"
#include "GameState.hpp"
#include <SFML/Window/WindowStyle.hpp>

// Durée pour 60 FPS
const sf::Time App::FrameRate = sf::Time(sf::seconds(1.f / 60.f));


////////////////////////////////////////////////////////////
App::App() :
  _window(sf::VideoMode(1280,960), "MasterMind",sf::Style::Titlebar | sf::Style::Close),
  _stateManager(&_context)
{
  _context.window       = &_window;
  _context.stateManager = &_stateManager;
  _stateManager.registerStates();
  _stateManager.setState(State::Menu);
}


////////////////////////////////////////////////////////////
App::~App()
{
  // TODO: Gestion d'erreur
}


////////////////////////////////////////////////////////////
void App::run()
{
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  
  while (_window.isOpen())
  {
    sf::Time timeElapsed = _clock.restart();
    timeSinceLastUpdate += timeElapsed;

    while (timeSinceLastUpdate > FrameRate)
    {
      timeSinceLastUpdate -= FrameRate;
      
      handleEvents();
      update(FrameRate);
    }

    draw();
  }
}


////////////////////////////////////////////////////////////
void App::handleEvents()
{
    sf::Event event;

    while (_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	_window.close();

      _stateManager.handleEvent(event);
    }
}


////////////////////////////////////////////////////////////
void App::update(sf::Time dt)
{
  _stateManager.update(dt);
}


////////////////////////////////////////////////////////////
void App::draw()
{
  _window.clear();
  _stateManager.draw();
  _window.display();
}

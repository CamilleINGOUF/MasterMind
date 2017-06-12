////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "NetworkState.hpp"
#include "GameStateManager.hpp"
#include "GameContext.hpp"

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
}


////////////////////////////////////////////////////////////
NetworkState::~NetworkState()
{
  
}


////////////////////////////////////////////////////////////
void NetworkState::update(sf::Time dt)
{
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
}

void NetworkState::switchToMenuState()
{
  GameStateManager* stateManager = _context->stateManager;
  stateManager->setState(State::Menu);
}

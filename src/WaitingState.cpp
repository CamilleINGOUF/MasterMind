////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "WaitingState.hpp"
#include "GameStateManager.hpp"
#include "GameContext.hpp"
#include "client.hpp"

#include <iostream>

////////////////////////////////////////////////////////////
WaitingState::WaitingState(GameContext* context) :
  GameState(context)
{
  if (!_font.loadFromFile("../media/fonts/arial.ttf"))
    exit(-1);

  _waitingText.setFont(_font);
  _waitingText.setString("En Attente...(2s)");
  _waitingText.setPosition(sf::Vector2f(50,50));
  _timeSinceStarted = 0.0;
}


////////////////////////////////////////////////////////////
WaitingState::~WaitingState()
{
  
}


////////////////////////////////////////////////////////////
void WaitingState::update(sf::Time dt)
{
  Client* client = _context->client;

  if (!client)
    return;
  
  if (client->isConnected())
    switchToNetworkState();
}


////////////////////////////////////////////////////////////
void WaitingState::handleEvent(sf::Event& event)
{
}


////////////////////////////////////////////////////////////
void WaitingState::draw()
{
  sf::RenderWindow* window = _context->window;
  window->draw(_waitingText);
}

void WaitingState::switchToNetworkState()
{
  GameStateManager* stateManager = _context->stateManager;
  stateManager->setState(State::InGame);
}

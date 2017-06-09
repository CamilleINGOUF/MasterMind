////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "GameStateManager.hpp"
#include "MenuState.hpp"

////////////////////////////////////////////////////////////
GameStateManager::GameStateManager() :
  _context(nullptr)
{
}

////////////////////////////////////////////////////////////
GameStateManager::GameStateManager(GameContext* context) :
  _context(context)
{
}


////////////////////////////////////////////////////////////
GameStateManager::~GameStateManager()
{
  for (auto itr = _gameStates.begin(); itr != _gameStates.end(); itr++)
  {
    delete itr->second;
    _gameStates.erase(itr);
  }
}


////////////////////////////////////////////////////////////
void GameStateManager::registerStates()
{
  _gameStates[State::Menu] = new MenuState(_context);
  //_gameStates[State::Waiting] = std::make_unique<WaitingState>(this);
  //_gameStates[State::InGame]  = std::make_unique<NetworkState>(this);
}


////////////////////////////////////////////////////////////
void GameStateManager::setState(State state)
{
  if (state == State::Menu)
  {
    _currentState = _gameStates[State::Menu];
  }
}


////////////////////////////////////////////////////////////
void GameStateManager::update(sf::Time dt)
{
  if (_currentState)
    _currentState->update(dt);
 }


////////////////////////////////////////////////////////////
void GameStateManager::handleEvent(sf::Event& event)
{
  if (_currentState)
    _currentState->handleEvent(event);
}


////////////////////////////////////////////////////////////
void GameStateManager::draw()
{
  if (_currentState)
    _currentState->draw();
}

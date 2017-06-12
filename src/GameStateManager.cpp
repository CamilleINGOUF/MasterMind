////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "GameStateManager.hpp"
#include "MenuState.hpp"
#include "JoiningState.hpp"
#include "NetworkState.hpp"

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
void GameStateManager::registerStates()
{
  _gameStates[State::Menu]    = std::make_unique<MenuState>(_context);
  _gameStates[State::Joining] = std::make_unique<JoiningState>(_context);
  _gameStates[State::InGame]  = std::make_unique<NetworkState>(_context);
}


////////////////////////////////////////////////////////////
void GameStateManager::setState(State state)
{
  if (state == State::Menu)
    _currentState = _gameStates[State::Menu].get();
  else if (state == State::Joining)
    _currentState = _gameStates[State::Joining].get();
  else if(state == State::InGame)
    _currentState = _gameStates[State::InGame].get();
  else
    _currentState = nullptr;
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

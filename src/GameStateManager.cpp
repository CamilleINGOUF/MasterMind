////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "AssetsDeclarations.hpp"
#include "AssetManager.hpp"
#include "GameStateManager.hpp"
#include "MenuState.hpp"
#include "JoiningState.hpp"
#include "NetworkState.hpp"


////////////////////////////////////////////////////////////
GameStateManager::GameStateManager() :
  GameStateManager(nullptr)
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
  _context->fontManager->load(Fonts::Arial, "../media/fonts/arial.ttf");
  _context->textureManager->load(Textures::Coin, "../media/images/tileset.png");
  _context->textureManager->load(Textures::PanelPions, "../media/images/mastermind_menu.png");
  _context->textureManager->load(Textures::BoardCombinaisons, "../media/images/backgroundCombinaisons.png");
  _context->textureManager->load(Textures::BoardCorrections, "../media/images/backgroundCorrections.png");
  _context->textureManager->load(Textures::BoardBackground, "../media/images/backgroundMastermind.png");
  _context->textureManager->load(Textures::BoardCoinsChoosen, "../media/images/backgroundCombiChoosen.png");
  _context->textureManager->load(Textures::Title, "../media/images/title.png");
  
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

  if (_currentState)
    _currentState->init();
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


////////////////////////////////////////////////////////////
GameState* GameStateManager::getCurrentState()
{
  return _currentState;
}

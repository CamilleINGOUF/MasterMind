#ifndef GAME_CONTEXT_HPP_
#define GAME_CONTEXT_HPP_

class GameStateManager;
namespace sf { class RenderWindow; }

////////////////////////////////////////////////////////////
/// \brief Le contexte du jeu. Il permet un accès plus simple
/// aux variables communes
///
////////////////////////////////////////////////////////////
struct GameContext
{
  sf::RenderWindow* window;
  GameStateManager* stateManager;
  // TODO: ResourceHolder ? FontHolder ?
};

#endif // GAME_CONTEXT_HPP_

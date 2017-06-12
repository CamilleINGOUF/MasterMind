#ifndef GAME_CONTEXT_HPP_
#define GAME_CONTEXT_HPP_

#include <string>

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
  
  std::string ip;
  std::string port;

  std::string clientName;
  std::string serverName;
  // TODO: ResourceHolder ? FontHolder ?
};

#endif // GAME_CONTEXT_HPP_

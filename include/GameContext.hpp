#ifndef GAME_CONTEXT_HPP_
#define GAME_CONTEXT_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <string>

class GameStateManager;
class Client;
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
  Client* client;
  
  std::string ip;
  std::string port;

  std::string clientName;
  std::string serverName;
};

#endif // GAME_CONTEXT_HPP_

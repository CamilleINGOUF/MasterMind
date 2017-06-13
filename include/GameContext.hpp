#ifndef GAME_CONTEXT_HPP_
#define GAME_CONTEXT_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "AssetsDeclarations.hpp"

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
  // Partie graphique
  sf::RenderWindow* window;
  GameStateManager* stateManager;
  TextureManager*   textureManager;
  FontManager*      fontManager;   
  
  // Partie réseau
  Client*           client;
  std::string       ip;
  unsigned short    port;
  std::string       clientName;
  std::string       serverName;
};

#endif // GAME_CONTEXT_HPP_

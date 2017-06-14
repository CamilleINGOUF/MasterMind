#ifndef GAME_CONTEXT_HPP_
#define GAME_CONTEXT_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "AssetsDeclarations.hpp"

#include <string>

class GameStateManager;
namespace sf { class RenderWindow; }
class MusicPlayer;

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
  MusicPlayer*      musicPlayer;
  
  // Partie réseau
  std::string       ip;
  unsigned short    port;
  std::string       clientName;
};

#endif // GAME_CONTEXT_HPP_

#ifndef APP_HPP_
#define APP_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "GameContext.hpp"
#include "GameStateManager.hpp"
#include "AssetManager.hpp"
#include "AssetsDeclarations.hpp"

#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
/// \brief La classe principale du jeu
///
////////////////////////////////////////////////////////////
class App
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Constructeur par défaut
  ///
  ////////////////////////////////////////////////////////////
  App();

  ////////////////////////////////////////////////////////////
  /// \brief Destructeur
  ///
  ////////////////////////////////////////////////////////////
  ~App();

  ////////////////////////////////////////////////////////////
  /// \brief La boucle principale
  ///
  ////////////////////////////////////////////////////////////
  void run();

  ////////////////////////////////////////////////////////////
  /// \brief Gestion des événements
  ///
  ////////////////////////////////////////////////////////////
  void handleEvents();

  ////////////////////////////////////////////////////////////
  /// \brief La partie logique du jeu
  ///
  /// \param dt le temps écoulé depuis la dernière frame
  ///
  ////////////////////////////////////////////////////////////
  void update(sf::Time dt);

  ////////////////////////////////////////////////////////////
  /// \brief Fonction d'affichage
  ///
  ////////////////////////////////////////////////////////////
  void draw();
  
  ////////////////////////////////////////////////////////////
  /// \brief Retourne le contexte de jeu
  ///
  /// \return Le contexte de jeu
  ///
  ////////////////////////////////////////////////////////////
  GameContext * getGameContext();
private:
  
  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  static const sf::Time FrameRate; ///< durée d'une frame

  sf::RenderWindow _window;         ///< Fenêtre principale
  GameStateManager _stateManager;   ///< Le gestionnaire d'états
  TextureManager   _textureManager; ///< Le gestionnaire des textures
  FontManager      _fontManager;    ///< Le gestionnaire des polices
  GameContext      _context;        ///< Le contexte de jeu
};

#endif // APP_HPP_

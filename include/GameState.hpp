#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "AssetManager.hpp"
#include "AssetsDeclarations.hpp"
#include "GameContext.hpp"

#include <memory>
#include <SFML/Graphics.hpp>


////////////////////////////////////////////////////////////
/// \brief Identifiants pour les différents états de jeu
///
////////////////////////////////////////////////////////////
enum State
{
  Menu,    ///< Le menu principal
  Joining, ///< Complétion du formulaire
  InGame   ///< En jeu
};

////////////////////////////////////////////////////////////
/// \brief Représente un état de jeu
///
////////////////////////////////////////////////////////////
class GameState
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Créer un état de jeu avec le contexte
  ///
  /// \param context le contexte de jeu
  ///
  ////////////////////////////////////////////////////////////  
  GameState(GameContext* context) :
    _context(context) {}

  ////////////////////////////////////////////////////////////
  /// \brief Le destructeur
  ///
  ////////////////////////////////////////////////////////////  
  virtual ~GameState() { }

  ////////////////////////////////////////////////////////////
  /// \brief Initialise l'état quand celui-ci devient l'état
  /// courant
  ///
  ////////////////////////////////////////////////////////////  
  virtual void init() = 0;
  
  ////////////////////////////////////////////////////////////
  /// \brief Boucle logique
  ///
  /// \param dt le temps de jeu
  ///
  ////////////////////////////////////////////////////////////  
  virtual void update(sf::Time dt) = 0;

  ////////////////////////////////////////////////////////////
  /// \brief Gestion d'évents
  ///
  /// \param event un événement
  ///
  ////////////////////////////////////////////////////////////  
  virtual void handleEvent(sf::Event& event) = 0;

  ////////////////////////////////////////////////////////////
  /// \brief Fonction d'affichage
  ///
  ////////////////////////////////////////////////////////////  
  virtual void draw() = 0;
  
protected:
  
  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////  
  GameContext* _context; ///< Le contexte du jeu
};

#endif // GAMESTATE_HPP_

#ifndef GAME_STATE_MANAGER_HPP_
#define GAME_STATE_MANAGER_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "GameContext.hpp"
#include "GameState.hpp"

#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

typedef std::map<State, std::unique_ptr<GameState>> StateContainer;

////////////////////////////////////////////////////////////
/// \brief Le gestionnaire d'états du jeu
///
////////////////////////////////////////////////////////////
class GameStateManager
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Constructeur par défaut
  ///
  ////////////////////////////////////////////////////////////
  GameStateManager();

  ////////////////////////////////////////////////////////////
  /// \brief Construit le gestionnaire d'états avec le contexte
  ///
  /// \param context le contexte de jeu
  ///
  ////////////////////////////////////////////////////////////
  GameStateManager(GameContext* context);
  
  ////////////////////////////////////////////////////////////
  /// \brief Création des différents stages du jeu
  ///
  ////////////////////////////////////////////////////////////  
  void registerStates();

  ////////////////////////////////////////////////////////////
  /// \brief Définit le nouvel état du jeu
  ///
  /// \param state void l'enum State
  ///
  ////////////////////////////////////////////////////////////  
  void setState(State state);

  ////////////////////////////////////////////////////////////
  /// \brief Boucle logique
  ///
  /// \param dt le temps écoulé depuis la dernière frame
  ///
  ////////////////////////////////////////////////////////////  
  void update(sf::Time dt);

  ////////////////////////////////////////////////////////////
  /// \brief Boucle logique
  ///
  /// \param event un événement
  ///
  ////////////////////////////////////////////////////////////  
  void handleEvent(sf::Event& event);

  ////////////////////////////////////////////////////////////
  /// \brief Rendu
  ///
  ////////////////////////////////////////////////////////////  
  void draw();

  ////////////////////////////////////////////////////////////
  /// \brief Retourne l'état courant
  ///
  ////////////////////////////////////////////////////////////  
  GameState* getCurrentState();
  
private:

  ////////////////////////////////////////////////////////////  
  /// Données membres
  ////////////////////////////////////////////////////////////  
  GameContext*   _context;      ///< Le contexte du jeu
  GameState*     _currentState; ///< L'état courant
  StateContainer _gameStates;   ///< Les états de jeu
};

#endif

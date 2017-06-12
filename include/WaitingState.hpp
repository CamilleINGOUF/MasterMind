#ifndef WAITING_STATE_HPP_
#define WAITING_STATE_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "GameState.hpp"

#include <SFML/Network.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

////////////////////////////////////////////////////////////
/// \brief Attente d'un autre joueur
////////////////////////////////////////////////////////////
class WaitingState : public GameState
{
public:
  WaitingState(GameContext* context);
  virtual ~WaitingState() override;
  virtual void update(sf::Time dt) override;
  virtual void handleEvent(sf::Event& event) override;
  virtual void draw() override;
private:
  void switchToNetworkState();
private:
  
  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  sf::Text _waitingText;   //< Texte affiché pendant l'attente
  sf::Font _font;          //< Police du texte

  float _timeSinceStarted; //< Temps depuis l'entrée dans l'état attente

  
};


#endif // WAITING_STATE_HPP_

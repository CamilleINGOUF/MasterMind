#ifndef NETWORK_STATE_HPP_
#define NETWORK_STATE_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "GameState.hpp"
#include "Button.hpp"
#include "Client.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

////////////////////////////////////////////////////////////
/// \brief Etat en jeu
////////////////////////////////////////////////////////////
class NetworkState : public GameState
{
public:
  NetworkState(GameContext* context);
  virtual ~NetworkState() override;
  virtual void update(sf::Time dt) override;
  virtual void handleEvent(sf::Event& event) override;
  virtual void draw() override;
private:
  void switchToMenuState();
private:
  
  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  sf::Text _waitingText;   //< Texte affiché pendant le jeu
  sf::Font _font;          //< Police du texte

  Button _backToMenu;      //< Bouton retour au menu
};


#endif // NETWORK_STATE_HPP_

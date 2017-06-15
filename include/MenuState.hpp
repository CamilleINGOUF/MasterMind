#ifndef MENU_STATE_HPP_
#define MENU_STATE_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "Button.hpp"
#include "GameState.hpp"
#include "TextField.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>


////////////////////////////////////////////////////////////
/// \brief Le menu principal
////////////////////////////////////////////////////////////
class MenuState : public GameState
{
public:
  MenuState(GameContext* context);
  virtual ~MenuState() override;
  virtual void init() override;
  virtual void update(sf::Time dt) override;
  virtual void handleEvent(sf::Event& event) override;
  virtual void draw() override;

private:
  
  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  Button _quit;
  Button _joinServer;
  sf::Sprite _background;
  sf::Sprite _title;
};


#endif // MENU_STATE_HPP_

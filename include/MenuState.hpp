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


////////////////////////////////////////////////////////////
/// \brief Le menu principal
////////////////////////////////////////////////////////////
class MenuState : public GameState
{
public:
  MenuState(GameContext* context);
  virtual ~MenuState() override;
  virtual void update(sf::Time dt) override;
  virtual void handleEvent(sf::Event& event) override;
  virtual void draw() override;

private:
  
  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  Button _quit;
  Button _joinServer;
};


#endif // MENU_STATE_HPP_

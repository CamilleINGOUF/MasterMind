#ifndef MENU_STATE_HPP_
#define MENU_STATE_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "GameState.hpp"
#include "Button.hpp"
#include "TextField.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

////////////////////////////////////////////////////////////
/// \brief Panels disponnibles
////////////////////////////////////////////////////////////
enum Panels
  {
    panel_menu,
    panel_join
  };

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
  void init();
  void switchPanels();
private:
  
  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  sf::Font _font;
  
  Button _quit;
  Button _joinServer;

  //< Panel pour rejoindre un serveur
  Button _cancel;
  Button _joinGame;

  TextField _addressHost;
  TextField _nickname;

  Panels _currentPanel;
};


#endif // MENU_STATE_HPP_

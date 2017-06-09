#ifndef _LAUNCHER_HPP
#define _LAUNCHER_HPP

#include "TextField.hpp"
#include "Button.hpp"

enum Panels
  {
    panel_menu,
    panel_join
  };

class Launcher
{
private:
  //< Panel de départ
  sf::Font _font;
  
  Button _quit;
  Button _joinServer;

  //< Panel pour rejoindre un serveur
  Button _cancel;
  Button _joinGame;

  TextField _addressHost;
  TextField _nickname;

  sf::RenderWindow _window;

  Panels _currentPanel;

  void init();
  void switchPanels();
public:
  Launcher();
  void run();
};

#endif

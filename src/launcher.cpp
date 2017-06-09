#include "launcher.hpp"
#include <SFML/Graphics.hpp>

#include <iostream>

Launcher::Launcher() :
  _window(sf::VideoMode(480, 240), "Mastermind")
{
  _currentPanel = panel_menu;
  init();
}

void Launcher::init()
{
  
  if (!_font.loadFromFile("../media/fonts/arial.ttf"))
    exit(-1);

  //< Quitter
  _quit.setFont(_font);
  _quit.setLabel("Quitter");
  _quit.setPosition(sf::Vector2f(200,150));
  _quit.setCallback([]()
		    {
		      exit(0);
		    });
  
  //< Rejoindre un serveur
  _joinServer.setFont(_font);
  _joinServer.setLabel("Rejoindre");
  _joinServer.setPosition(sf::Vector2f(180,100));
  _joinServer.setCallback([this](){
      switchPanels();
    });


  //< retour en arrière
  _cancel.setFont(_font);
  _cancel.setLabel("Retour");
  _cancel.setPosition(sf::Vector2f(200,150));
  _cancel.setCallback([this]()
		      {
			switchPanels();
		      });

  //< Rejoindre la partie
  _joinGame.setFont(_font);
  _joinGame.setLabel("Jouer");
  _joinGame.setPosition(sf::Vector2f(200,100));
  _joinGame.setCallback([]()
			{
		      
			});

  //_addressHost
  _addressHost.setFont(_font);
  _addressHost.setText("adresse:host");
  _addressHost.setPosition(sf::Vector2f(200,50));

  //_nickname
  _nickname.setFont(_font);
  _nickname.setText("pseudo");
  _nickname.setPosition(sf::Vector2f(200,0));

}

void Launcher::run()
{
  while(_window.isOpen())
    {

      sf::Event event;

      while (_window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    _window.close();

	  
	  
	 
	  if(_currentPanel == panel_menu)
	    {
	      
	      _quit.catchEvent(event);
	      _joinServer.catchEvent(event);
	    }
	  else
	    {
	      _nickname.catchEvent(event,_window);
	      _addressHost.catchEvent(event,_window);
	      _cancel.catchEvent(event);
	      _joinGame.catchEvent(event);
	    }
	}

      
      _window.clear(sf::Color::Black);
      if(_currentPanel == panel_menu)
	{
	  _window.draw(_quit);
	  _window.draw(_joinServer);
	}
      else
	{
	  _window.draw(_addressHost);
	  _window.draw(_nickname);
	  _window.draw(_cancel);
	  _window.draw(_joinGame); 
	}
      
      _window.display();
    }
}

void Launcher::switchPanels()
{
  if(_currentPanel == panel_menu)
    {
      _currentPanel = panel_join;
    }
  else
    {
      _currentPanel = panel_menu;
    }
}
  
// TESTS DU LAUNCHER
int main()
{
  Launcher launcher;
  launcher.run();
  return 0;
}


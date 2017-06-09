////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "MenuState.hpp"

#include <SFML/Graphics/Color.hpp>

////////////////////////////////////////////////////////////
MenuState::MenuState(GameContext* context) :
  GameState(context)
{
  init();
}


////////////////////////////////////////////////////////////
MenuState::~MenuState()
{
  
}


////////////////////////////////////////////////////////////
void MenuState::update(sf::Time dt)
{
}


////////////////////////////////////////////////////////////
void MenuState::handleEvent(sf::Event& event)
{
  sf::RenderWindow* window = _context->window;
  if(_currentPanel == panel_menu)
    {
	      
      _quit.catchEvent(event);
      _joinServer.catchEvent(event);
    }
  else
    {
      _nickname.catchEvent(event,*window);
      _addressHost.catchEvent(event,*window);
      _cancel.catchEvent(event);
      _joinGame.catchEvent(event);
    }
}


////////////////////////////////////////////////////////////
void MenuState::draw()
{
  sf::RenderWindow* window = _context->window;
  if(_currentPanel == panel_menu)
    {
      window->draw(_quit);
      window->draw(_joinServer);
    }
  else
    {
      window->draw(_addressHost);
      window->draw(_nickname);
      window->draw(_cancel);
      window->draw(_joinGame); 
    }
}

void MenuState::switchPanels()
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

void MenuState::init()
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

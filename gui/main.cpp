#include "SFML/Graphics.hpp"
#include <iostream>
#include "menu.h"


int main(){
  sf::RenderWindow renderWindow(sf::VideoMode(972, 640), "Mastermind");

  Menu menu(renderWindow.getSize().x, renderWindow.getSize().y);
  
  /*sf::Texture texture;
  if (!texture.loadFromFile("../img/mastermind.jpg")){
    renderWindow.close();
  }

  sf::Sprite background(texture);

  sf::RectangleShape rectangle(sf::Vector2f(120, 50));
  */
  while (renderWindow.isOpen()){
    sf::Event event;

    while (renderWindow.pollEvent(event)){
      switch (event.type)
	{
	case sf::Event::KeyReleased:
	  switch (event.key.code)
	    {
	    case sf::Keyboard::Up:
	      menu.MoveUp();
	      break;

	    case sf::Keyboard::Down:
	      menu.MoveDown();
	      break;

	    case sf::Keyboard::Return:
	      switch (menu.GetPressedItem())
		{
		case 0:
		  std::cout<< " Play appuyé" << std::endl;
		  break;
		case 1:
		  std::cout<< " Options appuyé" << std::endl;
		  break;
		case 2:
		  renderWindow.close();
		  break;
		}
	    }
	  break;
	case sf::Event::Closed:
	  renderWindow.close();
	  break;

	}
    }


      renderWindow.clear();
      /*renderWindow.draw(background);
	renderWindow.draw(rectangle);*/
      menu.draw(renderWindow);
      renderWindow.display();

  }
}

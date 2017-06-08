#include "SFML/Graphics.hpp"

#include <iostream>
#include "buttonMM.hpp"

int main(int argc, char** argv){
  sf::RenderWindow renderWindow(sf::VideoMode(972, 640), "Mastermind");
  sf::Texture texture;
  if (!texture.loadFromFile("../img/mastermind.jpg")){
    renderWindow.close();
  }

  sf::Sprite background(texture);

  bool pressed = false;

  //sf::RectangleShape rectangle(sf::Vector2f(120, 50));
  ButtonMM button(100,100,180,150,"Oui");

  while (renderWindow.isOpen()){
    sf::Event event;
    while (renderWindow.pollEvent(event)){
      if (event.type == sf::Event::EventType::Closed)
	{
	  renderWindow.close();
	}
      if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
	  if(!pressed)
	    {
	     
	      pressed = true;

	      if(button.isClicked(sf::Mouse::getPosition(renderWindow).x,
				  sf::Mouse::getPosition(renderWindow).y))
		std::cout << "Button clicked" << std::endl;
	    }
	}
      else
	{
	  pressed = false;
	}
    } 

      renderWindow.clear(sf::Color::White);
      renderWindow.draw(background);
      renderWindow.draw(button);
      renderWindow.display();

  }
}

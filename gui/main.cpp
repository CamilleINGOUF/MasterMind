#include "SFML/Graphics.hpp"


int main(int argc, char** argv){
  sf::RenderWindow renderWindow(sf::VideoMode(972, 640), "Mastermind");
  sf::Texture texture;
  if (!texture.loadFromFile("../img/mastermind.jpg")){
    renderWindow.close();
  }

  sf::Sprite background(texture);

  while (renderWindow.isOpen()){
    sf::Event event;

    while (renderWindow.pollEvent(event)){
      if (event.type == sf::Event::EventType::Closed)
      {
        renderWindow.close();
      }

      if (event.type == sf::Event::EventType::KeyPressed)
      {
      }
    } 

      renderWindow.clear(sf::Color::White);
      renderWindow.draw(background);
      renderWindow.display();

  }
}

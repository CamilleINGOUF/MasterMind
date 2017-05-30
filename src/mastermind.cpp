/////////////////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////////////////
#include "mastermind.hpp"

////////////////////////////////////////////////////////////
MasterMind::MasterMind() :
  _window(sf::VideoMode(640, 480), "SFML Works !")
{
  
}


/////////////////////////////////////////////////////////////
void MasterMind::run()
{
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);
  
    
  while (_window.isOpen())
  {
    sf::Event event;

    while (_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	_window.close();
    }

    _window.clear();
    _window.draw(shape);
    _window.display();
  }
}

bool MasterMind::foo(int a)
{
  return true;
}

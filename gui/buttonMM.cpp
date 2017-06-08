#include "buttonMM.hpp"

ButtonMM::ButtonMM() :
  _pAX(0), _pAY(0), _pBX(120), _pBY(50), _rectangle({120,50})
{
  _font.loadFromFile("../media/fonts/DejaVuSans-Bold.ttf");
  _text.setString("Button");
  _text.setFont(_font);
  _text.setColor(sf::Color::Black);
  _text.setPosition(_pAX + 10,_pAY + 5);
}

ButtonMM::ButtonMM(int ax, int ay, int bx, int by, std::string text) :
  _pAX(ax), _pAY(ay), _pBX(bx), _pBY(by),
  _rectangle({(float)(bx-ax),(float)(by-ay)})
{
  _rectangle.setPosition(_pAX,_pAY);
  _font.loadFromFile("../media/fonts/DejaVuSans-Bold.ttf");
  _text.setString(text);
  _text.setFont(_font);
  _text.setColor(sf::Color::Black);
  _text.setPosition(_pAX + 10,_pAY + 5);
}

void ButtonMM::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_rectangle,states);
  target.draw(_text, states);
}

bool ButtonMM::isClicked(int x,int y)
{
  return (
	  x >= _pAX and
	  x <= _pBX and
	  y >= _pAY and
	  y <= _pBY
	  );
}

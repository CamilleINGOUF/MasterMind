#ifndef _BUTTON_MM_HPP
#define _BUTTON_MM_HPP

#include "SFML/Graphics.hpp"
#include <string>

class ButtonMM : public sf::Drawable
{
private:
  int _pAX; //< abscisse point supérieur gauche
  int _pAY; //< ordonnée point supérieur gauche

  int _pBX; //< abscisse point inférieur droit
  int _pBY; //< ordonnée point inférieur droit

  sf::RectangleShape _rectangle;
  sf::Font _font;
  sf::Text _text;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
  ButtonMM();
  ButtonMM(int ax, int ay, int bx, int by, std::string text);

  bool isClicked(int x, int y);
};

#endif

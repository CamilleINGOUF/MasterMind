#ifndef _PANEL_PION_HPP
#define _PANEL_PION_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Pion.hpp"
#include "PionDrawable.hpp"

class PanelPions : public sf::Drawable
{
public:
  PanelPions();

  Pion catchEvent(sf::Event& event);

  void setPosition(const sf::Vector2f& pos);

  void setScale(const sf::Vector2f& factors);
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  std::vector<Pion> _pions;
  std::vector<PionDrawable> _pionsD;

  sf::RectangleShape _rectangle;
};

#endif
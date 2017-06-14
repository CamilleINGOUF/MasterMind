////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "PanelPions.hpp"

#include <iostream>

////////////////////////////////////////////////////////////
PanelPions::PanelPions(TextureManager* textureManager) :
  _textureManager(textureManager),
  _rectangle(sf::Vector2f(108, 170)),
  _pions({rouge, jaune, marron, bleu, blanc, noir, vert, orange})
{
  _rectangle.setFillColor(sf::Color::White);
  
  for (const Pion& pion : _pions)
      _pionsD.push_back(PionDrawable(pion, textureManager));
   
  setPositionPions();
}


////////////////////////////////////////////////////////////
Pion PanelPions::catchEvent(sf::Event& event)
{
  
  for (PionDrawable& p : _pionsD)
  {
    if (p.catchEvent(event))
    {
      return p.getPion();
    }
  }
  
  return Pion(Couleur::vide);
}


////////////////////////////////////////////////////////////
void PanelPions::setPosition(const sf::Vector2f& pos)
{
  _rectangle.setPosition(pos);
  setPositionPions();
}


////////////////////////////////////////////////////////////
void PanelPions::setPositionPions()
{
  for (unsigned i = 0; i < _pionsD.size(); i++)
  {
    if (i % 2 == 0)
    {
      sf::Vector2f pos(_rectangle.getPosition().x + 4,
		       _rectangle.getPosition().y +
		       (i * 20));
      _pionsD[i].setPosition(pos);
    }
    else
    {
      sf::Vector2f pos(_rectangle.getPosition().x + 52,
		       _rectangle.getPosition().y +
		       ((i-1) * 20));
      _pionsD[i].setPosition(pos);
    }
  }
}


////////////////////////////////////////////////////////////
void PanelPions::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_rectangle,states);

  for (const PionDrawable& p : _pionsD)
    target.draw(p);
}

#include "PionDrawable.hpp"

////////////////////////////////////////////////////////////
PionDrawable::PionDrawable()
{}

PionDrawable::PionDrawable(Pion pion) :
  _pion(pion)
{
  if(!_texture.loadFromFile("../media/images/pions/pion_"+(*pion.getString())+".png"))
    {
      std::cerr << "Pas trouvé l'image du pion [!]" << std::endl;
      exit(0);
    }
  _sprite.setTexture(_texture);
}

void PionDrawable::setPion(const Pion& p)
{
  _pion = p;
   if(!_texture.loadFromFile("../media/images/pions/pion_"+(*_pion.getString())+".png"))
    {
      std::cerr << "Pas trouvé l'image du pion [!]" << std::endl;
      exit(0);
    }
  _sprite.setTexture(_texture);
}

////////////////////////////////////////////////////////////
void PionDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_sprite,states);
}

void PionDrawable::setPosition(const sf::Vector2f& pos)
{
  _sprite.setPosition(pos);
}

void PionDrawable::setScale(const sf::Vector2f& factors)
{
  _sprite.setScale(factors);
}

#include "correctionDrawable.hpp"

CorrectionDrawable::CorrectionDrawable() :
  _pion(blanc)
{
  updateSprite();
}

CorrectionDrawable::CorrectionDrawable(Pion p, TextureManager* text) :
  _pion(p), _textureManager(text)
{
  _sprite.setTexture(_textureManager->get(Textures::Coin));
  updateSprite();
}

void CorrectionDrawable::setPion(const Pion& p)
{
  _pion = p;
  updateSprite();
}

void CorrectionDrawable::setPosition(const sf::Vector2f& pos)
{
  _sprite.setPosition(pos);
}

Pion CorrectionDrawable::getPion() const
{
  return _pion;
}

void CorrectionDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_sprite,states);
}

void CorrectionDrawable::updateSprite()
{
  Couleur c = _pion.getCouleur();
  
  sf::IntRect rect(0,16,16,16);
  switch(c)
    {
    case noir:
      rect.left = 0;
      break;
    case blanc:
      rect.left = 16;
      break;
    case vide:
      rect.left = 112;
      rect.top = 16;
      break;
    default:
      return;
    }
  _sprite.setTextureRect(rect);
  _sprite.setScale(sf::Vector2f(4,4));
}

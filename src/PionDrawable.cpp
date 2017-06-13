#include "PionDrawable.hpp"


////////////////////////////////////////////////////////////
PionDrawable::PionDrawable() :
_pion(blanc)
{
  updateSprite();
}

PionDrawable::PionDrawable(Pion pion, TextureManager* text) :
  _pion(pion), _textureManager(text)
{
  _sprite.setTexture(_textureManager->get(Textures::Coin));
  updateSprite();
}

void PionDrawable::setPion(const Pion& p)
{
  _pion = p;
  updateSprite();
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

void PionDrawable::setTextureManager(TextureManager* text)
{
  _textureManager = text;
}

void PionDrawable::updateSprite()
{
  Couleur c = _pion.getCouleur();
  sf::IntRect rect(0,0,16,16);
  switch(c)
    {
    case rouge:
      rect.left = 0;
      break;
    case vert:
      rect.left = 16;
      break;
    case jaune:
      rect.left = 32;
      break;
    case orange:
      rect.left = 48;
      break;
    case marron:
      rect.left = 64;
      break;
    case noir:
      rect.left = 80;
      break;
    case blanc:
      rect.left = 96;
      break;
    case bleu:
      rect.left = 112;
      break;
    }
  _sprite.setTextureRect(rect);
}

#include "PlateauDrawable.hpp"

PlateauDrawable::PlateauDrawable(TextureManager* text) :
  _textureManager(text)
{}

void PlateauDrawable::catchEvent(sf::Event& event)
{}

void PlateauDrawable::setPosition(const sf::Vector2f& pos)
{}

void PlateauDrawable::setTextureManager(TextureManager* text)
{}

void PlateauDrawable::draw(sf::RenderTarget& target, sf::RenderStates states)
  const
{}

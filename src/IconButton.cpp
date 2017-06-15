////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "IconButton.hpp"

#include <iostream>
#include <stdexcept>
#include <memory>


////////////////////////////////////////////////////////////
IconButton::IconButton(const sf::Sprite& sprite,
		       const sf::Sprite& activeSprite) :
  _sprite(sprite),
  _activeSprite(activeSprite),
  _active(true)
{
}


////////////////////////////////////////////////////////////
void IconButton::catchEvent(sf::Event &event)
{
  if (event.type != sf::Event::MouseButtonPressed)
    return;

  if (event.mouseButton.button != sf::Mouse::Left)
    return;

  sf::FloatRect buttonRect = _sprite.getGlobalBounds();

  if (buttonRect.contains(event.mouseButton.x, event.mouseButton.y))
  {
    if (_callback)
    {
      _active = !_active;
      _callback();
    }
  }
}


////////////////////////////////////////////////////////////
void IconButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (!_active)
    target.draw(_sprite, states);
  else
    target.draw(_activeSprite, states);
}


////////////////////////////////////////////////////////////
void IconButton::setPosition(const sf::Vector2f &position)
{
  _sprite.setPosition(position);
  _activeSprite.setPosition(position);
}


////////////////////////////////////////////////////////////
void IconButton::setCallback(Callback callback)
{
  _callback = std::move(callback);
}


////////////////////////////////////////////////////////////
bool IconButton::isActive() const
{
  return _active;
}


////////////////////////////////////////////////////////////
void IconButton::activate()
{
  _active = true;
}

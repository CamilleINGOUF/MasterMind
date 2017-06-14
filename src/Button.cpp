////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "Button.hpp"

#include <iostream>
#include <stdexcept>
#include <memory>


////////////////////////////////////////////////////////////
Button::Button() :
  Button(nullptr, "")
{
}


////////////////////////////////////////////////////////////
Button::Button(FontManager* fontManager, const std::string& label) :
  _fontManager(fontManager),
  _background(sf::Color(162,38,51)),
  _textColor(sf::Color::White)
{
  _text.setFont(_fontManager->get(Fonts::Arial));
  _text.setString(label);
  _shape.setFillColor(_background);
  _text.setColor(_textColor);
  updateGeometry();
}


////////////////////////////////////////////////////////////
void Button::updateGeometry()
{
  sf::FloatRect bounds = _text.getGlobalBounds();
  _shape.setSize(sf::Vector2f(bounds.width + 10, bounds.height + 10));
  _shape.setPosition(bounds.left - 5, bounds.top - 5);
}


////////////////////////////////////////////////////////////
void Button::catchEvent(sf::Event &event)
{
  if (event.type != sf::Event::MouseButtonPressed)
    return;

  if (event.mouseButton.button != sf::Mouse::Left)
    return;

  sf::FloatRect buttonRect = _shape.getGlobalBounds();

  if (buttonRect.contains(event.mouseButton.x, event.mouseButton.y))
  {
    if (_callback)
      _callback();
  }
}


////////////////////////////////////////////////////////////
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (!_text.getFont())
    throw std::runtime_error("Button with invalid font !");

  target.draw(_shape, states);
  target.draw(_text, states);
}


////////////////////////////////////////////////////////////
void Button::setLabel(const std::string& label)
{
  _text.setString(label);
  updateGeometry();
}


////////////////////////////////////////////////////////////
void Button::setPosition(const sf::Vector2f &position)
{
  _text.setPosition(position);
  updateGeometry();
}


////////////////////////////////////////////////////////////
void Button::setBackground(const sf::Color& background)
{
  _background = background;
}


////////////////////////////////////////////////////////////
void Button::setTextColor(const sf::Color &color)
{
  _text.setColor(color);
}


////////////////////////////////////////////////////////////
void Button::setCallback(Callback callback)
{
  _callback = std::move(callback);
}

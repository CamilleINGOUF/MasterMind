////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "Button.hpp"

#include <iostream>
#include <stdexcept>
#include <memory>


////////////////////////////////////////////////////////////
Button::Button() :
  _background(sf::Color::Red),
  _textColor(sf::Color::White)
{
  setup();
}


////////////////////////////////////////////////////////////
Button::Button(const sf::Font& font, const std::string& label) :
  _text(label, font),
  _background(sf::Color::Red),
  _textColor(sf::Color::White)
{
  setup();
}


////////////////////////////////////////////////////////////
void Button::updateGeometry()
{
  sf::FloatRect bounds = _text.getGlobalBounds();
  _shape.setSize(sf::Vector2f(bounds.width, bounds.height));
  _shape.setPosition(bounds.left, bounds.top);
}


////////////////////////////////////////////////////////////
void Button::setup()
{
  _shape.setFillColor(_background);
  _text.setColor(_textColor);
  updateGeometry();
}


////////////////////////////////////////////////////////////
void Button::catchEvent(sf::Event &event)
{
  if (event.type != sf::Event::MouseButtonPressed)
    return;

  if (event.mouseButton.button != sf::Mouse::Left)
    return;

  sf::FloatRect buttonRect = _text.getGlobalBounds();

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

  target.draw(_shape);
  target.draw(_text);
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

////////////////////////////////////////////////////////////
void Button::setFont(const sf::Font& font)
{
  _text.setFont(font);
}

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "TextField.hpp"
#include <stdexcept>
#include <iostream>

TextField::TextField() : 
  _backgroundColor(sf::Color::Red),
  _outlineColor(sf::Color::White)
{
  _background.setSize(sf::Vector2f(200, 25));
  _background.setFillColor(_backgroundColor);
  _background.setOutlineColor(_outlineColor);
  _maxLength = 20;
  _background.setOutlineThickness(1);
  isActive = false;
}


////////////////////////////////////////////////////////////
TextField::TextField(const sf::Font& font) :
  TextField(font, 20, "")
{
}


////////////////////////////////////////////////////////////
TextField::TextField(const sf::Font& font, const unsigned maxLength) :
  TextField(font, maxLength, "")
{
}


////////////////////////////////////////////////////////////
TextField::TextField(const sf::Font& font, const unsigned maxLength,
		     const std::string& text) :
  _text(text, font, 20),
  _maxLength(maxLength),
  _backgroundColor(sf::Color::Red),
  _outlineColor(sf::Color::White)
{
  _background.setSize(sf::Vector2f(200, 25));
  _background.setFillColor(_backgroundColor);
  _background.setOutlineColor(_outlineColor);
  _background.setOutlineThickness(1);
  isActive = false;
}


////////////////////////////////////////////////////////////
void TextField::catchEvent(sf::Event& event, const sf::RenderWindow& window)
{
  // Catch seulement des saisies clavier
  if (event.type != sf::Event::TextEntered
      and event.type != sf::Event::MouseButtonPressed)
    return;

  if(event.type == sf::Event::MouseButtonPressed)
    {
      if(sf::Mouse::getPosition(window).x >= _background.getPosition().x &&
	 sf::Mouse::getPosition(window).y >= _background.getPosition().y &&
	 sf::Mouse::getPosition(window).x <= _background.getPosition().x + _background.getSize().x &&
	 sf::Mouse::getPosition(window).y <= _background.getPosition().y + _background.getSize().y)
	  isActive = true;
      else
	  isActive = false;
      return;
    }

  // Accepte uniquement les caractères (pas d'accents)
  // Entrée ne fait rien !
  if (event.text.unicode > 127 or event.text.unicode == 13)
    return;

  // Backspace
  if (event.text.unicode == 8 && isActive)
  {
    sf::String str   = _text.getString();
    std::size_t size = str.getSize();

    // Il y a au moins un caractère à supprimer
    if (size > 0)
    {
      str.erase(size - 1);
      _text.setString(str);
    }

    return;
  }
  
  // Vérification de la limite
  if (_text.getString().getSize() == _maxLength or !isActive)
    return;
  
  // Ajout de la lettre frappée
  char c = static_cast<char>(event.text.unicode);
  _text.setString(_text.getString() + c);
}


////////////////////////////////////////////////////////////
void TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (!_text.getFont())
    throw std::runtime_error("TextField with invalid font !");

  target.draw(_background);
  target.draw(_text);
}


////////////////////////////////////////////////////////////
void TextField::setFont(const sf::Font& font)
{
  _text.setFont(font);
}  


////////////////////////////////////////////////////////////
void TextField::setPosition(const sf::Vector2f& position)
{
  _text.setPosition(position.x, position.y);
  _background.setPosition(position.x, position.y);
}


////////////////////////////////////////////////////////////
void TextField::setBackgroundColor(const sf::Color& backgroundColor)
{
  _backgroundColor = backgroundColor;
}


////////////////////////////////////////////////////////////
void TextField::setOutlineColor(const sf::Color& outlineColor)
{
  _outlineColor = outlineColor;
}


////////////////////////////////////////////////////////////
const std::string& TextField::getText()
{
  return _text.getString();
}


////////////////////////////////////////////////////////////
void TextField::setText(const std::string& text)
{
  _text.setString(text);
}


////////////////////////////////////////////////////////////
void TextField::setBackgroundSize(const sf::Vector2f& size)
{
  _background.setSize(size);
}

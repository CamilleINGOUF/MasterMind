////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "TextField.hpp"
#include <stdexcept>
#include <iostream>

TextField::TextField() : 
  TextField(nullptr, "", 20)
{
}


////////////////////////////////////////////////////////////
TextField::TextField(FontManager* fontManager, const std::string& text) :
  TextField(fontManager, text, 20)
{
}


////////////////////////////////////////////////////////////
TextField::TextField(FontManager* fontManager, const std::string& text,
		     const unsigned maxLength) :
  _fontManager(fontManager),
  _maxLength(maxLength),
  _backgroundColor(sf::Color::Red),
  _outlineColor(sf::Color::White),
  _isActive(false)
{
  _background.setSize(sf::Vector2f(200, 25));
  _background.setFillColor(_backgroundColor);
  _background.setOutlineColor(_outlineColor);
  _background.setOutlineThickness(1);

  _text.setFont(_fontManager->get(Fonts::Arial));
  _text.setCharacterSize(20);
  _text.setString(text);
}


////////////////////////////////////////////////////////////
void TextField::catchEvent(sf::Event& event)
{
  // Catch seulement des saisies clavier
  if (event.type != sf::Event::TextEntered
      and event.type != sf::Event::MouseButtonPressed)
    return;

  // Check du focus
  if (event.type == sf::Event::MouseButtonPressed)
  {
    int mouseX = event.mouseButton.x;
    int mouseY = event.mouseButton.y;
    
    if (mouseX >= _background.getPosition().x &&
	mouseY >= _background.getPosition().y &&
	mouseX <= _background.getPosition().x + _background.getSize().x &&
	mouseY <= _background.getPosition().y + _background.getSize().y)
          _isActive = true;
      else
	  _isActive = false;

    return;
  }

  if (!_isActive) return;

  // Accepte uniquement les caractères (pas d'accents)
  // Entrée ne fait rien !
  if (event.text.unicode > 127 or event.text.unicode == 13)
    return;

  // Backspace
  if (event.text.unicode == 8)
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
  if (_text.getString().getSize() == _maxLength)
    return;
  
  // Ajout de la lettre frappée
  char c = static_cast<char>(event.text.unicode);
  _text.setString(_text.getString() + c);
}


////////////////////////////////////////////////////////////
void TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_background);
  target.draw(_text);
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
const sf::String& TextField::getText()
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

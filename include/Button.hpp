#ifndef BUTTON_HPP_
#define BUTTON_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <functional>

typedef std::function<void()> Callback;

////////////////////////////////////////////////////////////
/// \brief Un bouton contenant un label
///
////////////////////////////////////////////////////////////
class Button : public sf::Drawable
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Construit un bouton avec une police et un texte 
  /// par défaut
  ///
  /// \param font la police du bouton
  /// \param label le label du bouton
  ///
  ////////////////////////////////////////////////////////////
  Button(const sf::Font& font, const std::string& label);

  ////////////////////////////////////////////////////////////
  /// \brief Attrape les événements pour mettre à jour le bouton
  ///
  /// \param event voir sf::Event
  ///
  ////////////////////////////////////////////////////////////
  void catchEvent(sf::Event& event);

  ////////////////////////////////////////////////////////////
  /// \brief Définit le texte du button
  ///
  /// \param label le texte du button
  ///
  ////////////////////////////////////////////////////////////
  void setLabel(const std::string& label);

  ////////////////////////////////////////////////////////////
  /// \brief Définit la position du bouton
  ///
  /// \param position la nouvelle position du bouton
  ///
  ////////////////////////////////////////////////////////////
  void setPosition(const sf::Vector2f& position);

  ////////////////////////////////////////////////////////////
  /// \brief Définit la couleur de fond du bouton
  ///
  /// \param background la couleur de fond du bouton
  ///
  ////////////////////////////////////////////////////////////
  void setBackground(const sf::Color& background);

  ////////////////////////////////////////////////////////////
  /// \brief Définit la couleur du label
  ///
  /// \param color la nouvelle couleur du label
  ///
  ////////////////////////////////////////////////////////////
  void setTextColor(const sf::Color& color);

  ////////////////////////////////////////////////////////////
  /// \brief Définit l'event du bouton
  ///
  /// \param callback l'event du bouton
  ///
  ////////////////////////////////////////////////////////////
  void setCallback(Callback callback);

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  ////////////////////////////////////////////////////////////
  /// \brief Recalcule la position et la taille du background
  /// par rapport au texte.
  ///
  ////////////////////////////////////////////////////////////  
  void priv_updateGeometry();

  ////////////////////////////////////////////////////////////  
  /// Données membres
  ////////////////////////////////////////////////////////////  
  sf::Text _text;            ///< Rendu du texte
  sf::RectangleShape _shape; ///< Le background
  sf::Color _background;     ///< Le couleur du background
  sf::Color _textColor;      ///< La couleur du label
  Callback _callback;        ///< L'event associé au bouton
};

#endif // BUTTON_HPP_

////////////////////////////////////////////////////////////
/// \class Button
///
/// Exemple d'utilisation:
/// \code
/// Button button(font, "Mon bouton !");
/// button.setPosition(sf::Vector2f(200, 200));
/// button.setCallback([this](){...}); // A appeler dans une classe
/// ...
/// while(window.pollEvent(event)) { button.catchEvent(event); ... }
/// \endcode
///
////////////////////////////////////////////////////////////

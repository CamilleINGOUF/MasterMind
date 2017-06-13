#ifndef TEXTFIELD_HPP_
#define TEXTFIELD_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "AssetsDeclarations.hpp"
#include "AssetManager.hpp"

#include <SFML/Graphics.hpp>


////////////////////////////////////////////////////////////
/// \brief Champ d'entrée
///
////////////////////////////////////////////////////////////
class TextField : public sf::Drawable
{
public:
  
  ////////////////////////////////////////////////////////////
  /// \brief Constructeur par défaut
  ///
  ////////////////////////////////////////////////////////////
  TextField();
  
  ////////////////////////////////////////////////////////////
  /// \brief Construit un text field avec une chaîne de caractères
  ///
  /// \param fontManager le gestionnaire de polices
  /// \param text la police du textfield
  ///
  ////////////////////////////////////////////////////////////
  TextField(FontManager* fontManager, const std::string& text);

  ////////////////////////////////////////////////////////////
  /// \brief Construit un text field avec une police, un nombre
  /// maximum de caractères et définit le texte par défaut
  ///
  /// \param fontManager le gestionnaire de polices
  /// \param text le texte par défaut du champ
  /// \param maxLength le nombre maximal de caractère
  ///
  ////////////////////////////////////////////////////////////
  TextField(FontManager* fontManager, const std::string& text,
	    const unsigned maxLength);

  ////////////////////////////////////////////////////////////
  /// \brief Retourne la chaîne de caractère contenue
  /// dans le textfield
  ///
  /// \return Le contenu du textfield
  ///
  ////////////////////////////////////////////////////////////
  const sf::String& getText();

  ////////////////////////////////////////////////////////////
  /// \brief Définit le contenu du textfield
  ///
  /// \param text le contenu du textfield
  ///
  ////////////////////////////////////////////////////////////
  void setText(const std::string& text);

  ////////////////////////////////////////////////////////////
  /// \brief Met à jour le champ d'entrée en fonction des events
  ///
  /// \param event voir sf::Event
  ///
  ////////////////////////////////////////////////////////////
  void catchEvent(sf::Event& event);

  ////////////////////////////////////////////////////////////
  /// \brief Définit la posiion du textfield
  ///
  /// \param position la nouvelle position
  ///
  ////////////////////////////////////////////////////////////
  void setPosition(const sf::Vector2f& position);

  ////////////////////////////////////////////////////////////
  /// \brief Définit la couleur du background
  ///
  /// \param background la nouvelle couleur de background
  ///
  ////////////////////////////////////////////////////////////
  void setBackgroundColor(const sf::Color& background);

  ////////////////////////////////////////////////////////////
  /// \brief Définit la couleur du contour du background
  ///
  /// \param background la nouvelle couleur du contour du background
  ///
  ////////////////////////////////////////////////////////////
  void setOutlineColor(const sf::Color& outline);

  ////////////////////////////////////////////////////////////
  /// \brief Définit la taille du background
  ///
  /// \param size la nouvelle taille du background
  ///
  ////////////////////////////////////////////////////////////
  void setBackgroundSize(const sf::Vector2f& size);
  
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
  ////////////////////////////////////////////////////////////
  /// Données membres
  //////////////////////////////////////////////////////////// 
  FontManager*       _fontManager;     ///< Le gestionnaire de polices
  sf::Text           _text;            ///< Instance de texte
  unsigned           _maxLength;       ///< Le nombre maximum de caractères
  sf::RectangleShape _background;      ///< Le rectangle qui sert de background
  sf::Color          _backgroundColor; ///< La couleur de fond
  sf::Color          _outlineColor;    ///< La couleur de contour du background
  bool               _isActive;        ///< Si on écrit dedans ou pas
};

#endif

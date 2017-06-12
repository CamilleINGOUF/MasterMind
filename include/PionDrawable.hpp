#ifndef _PION_DRAWABLE_HPP
#define _PION_DRAWABLE_HPP

#include <SFML/Graphics.hpp>

#include "Pion.hpp"

class PionDrawable : public sf::Drawable
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Constructeur par défaut
  ////////////////////////////////////////////////////////////
  PionDrawable();

  ////////////////////////////////////////////////////////////
  /// \brief Constructeur avec pion
  ////////////////////////////////////////////////////////////
  PionDrawable(Pion p);

  void setPion(const Pion& p);

  ////////////////////////////////////////////////////////////
  /// \brief detecte les évènements
  /// 
  /// \param event voir sf::Event
  ////////////////////////////////////////////////////////////
  void catchEvent(sf::Event& event);

  ////////////////////////////////////////////////////////////
  /// \brief Définit la posiion du pion
  ///
  /// \param position la nouvelle position
  ///
  /////////////////////////////////////////////////////////
  void setPosition(const sf::Vector2f& pos);

  void setScale(const sf::Vector2f& factors);
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  Pion _pion;

  sf::Texture _texture;
  sf::Sprite _sprite;
};

#endif

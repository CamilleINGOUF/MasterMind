#ifndef _PION_DRAWABLE_HPP
#define _PION_DRAWABLE_HPP

#include <SFML/Graphics.hpp>

#include "AssetsDeclarations.hpp"
#include "AssetManager.hpp"

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
  PionDrawable(Pion p, TextureManager* text);

  void setPion(const Pion& p);

  ////////////////////////////////////////////////////////////
  /// \brief detecte les évènements
  /// 
  /// \param event voir sf::Event
  ////////////////////////////////////////////////////////////
  bool catchEvent(sf::Event& event);

  ////////////////////////////////////////////////////////////
  /// \brief Définit la posiion du pion
  ///
  /// \param pos la nouvelle position
  ///
  /////////////////////////////////////////////////////////
  void setPosition(const sf::Vector2f& pos);

  Pion getPion() const;

  void setScale(const sf::Vector2f& factors);

  void setTextureManager(TextureManager* text);
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  void updateSprite();

  Pion _pion;

  sf::Sprite _sprite;

  TextureManager* _textureManager;
};

#endif

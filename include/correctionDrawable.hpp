#ifndef _CORRECTION_DRAWABLE_HPP
#define _CORRECTION_DRAWABLE_HPP

#include <SFML/Graphics.hpp>

#include "AssetsDeclarations.hpp"
#include "AssetManager.hpp"

#include "Pion.hpp"

class CorrectionDrawable : public sf::Drawable
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Constructeur par défaut
  ////////////////////////////////////////////////////////////
  CorrectionDrawable();

  ////////////////////////////////////////////////////////////
  /// \brief Constructeur avec pion
  ////////////////////////////////////////////////////////////
  CorrectionDrawable(Pion p, TextureManager* text);

  void setPion(const Pion& p);
  
  ////////////////////////////////////////////////////////////
  /// \brief Définit la posiion du pion
  ///
  /// \param pos la nouvelle position
  ///
  /////////////////////////////////////////////////////////
  void setPosition(const sf::Vector2f& pos);

  Pion getPion() const;

  bool doBoard(std::string board);
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  void updateSprite();

  Pion _pion;

  sf::Sprite _sprite;

  TextureManager* _textureManager;
};

#endif

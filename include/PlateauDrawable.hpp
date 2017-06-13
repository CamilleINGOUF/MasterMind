#ifndef _PLATEAU_DRAWABLE_HPP
#define _PLATEAU_DRAWABLE_HPP

#include <SFML/Graphics.hpp>

#include "AssetsDeclarations.hpp"
#include "AssetManager.hpp"
#include "PanelPions.hpp"

class PlateauDrawable : public sf::Drawable
{
public:
  PlateauDrawable(TextureManager* text);

  void catchEvent(sf::Event& event);

  void setPosition(const sf::Vector2f& pos);

  void setTextureManager(TextureManager* text);
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  TextureManager* _textureManager;
};

#endif

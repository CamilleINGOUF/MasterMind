#ifndef _PANEL_PION_HPP
#define _PANEL_PION_HPP

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "AssetsDeclarations.hpp"
#include "AssetManager.hpp"
#include "Pion.hpp"
#include "PionDrawable.hpp"


#include <SFML/Graphics.hpp>
#include <vector>

class PanelPions : public sf::Drawable
{
public:
  PanelPions(TextureManager* text);

  Pion catchEvent(sf::Event& event);

  void setPosition(const sf::Vector2f& pos);

  void setTextureManager(TextureManager* text);
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  void setPositionPions();

  std::vector<Pion> _pions;
  std::vector<PionDrawable> _pionsD;

  sf::RectangleShape _rectangle;

  TextureManager* _textureManager;
};

#endif

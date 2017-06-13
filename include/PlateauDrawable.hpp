#ifndef _PLATEAU_DRAWABLE_HPP
#define _PLATEAU_DRAWABLE_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "AssetsDeclarations.hpp"
#include "AssetManager.hpp"
#include "PanelPions.hpp"
#include "Button.hpp"

class PlateauDrawable : public sf::Drawable
{
public:
  PlateauDrawable(TextureManager* text, FontManager* font);

  void catchEvent(sf::Event& event);

  void setPosition(const sf::Vector2f& pos);
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  TextureManager* _textureManager;
  FontManager* _fontManager;

  //available coins
  PanelPions _panelPions;

  // Choosen coins (on screen)
  std::vector<PionDrawable> _pionsDChoosen;
  std::vector<Pion> _pionsChoosen;

  int indexNextPion;
  
  sf::RectangleShape _backgroundChoosenCoins;
  //Button _validateButton;
  Button _resetButton;
  ////////////////////////////
};

#endif

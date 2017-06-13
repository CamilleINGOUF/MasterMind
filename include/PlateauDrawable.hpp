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

  void reset();

  std::vector<Pion> getValidatedCombi();
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  void validateCombi();
  
  Button _validateButton;
  Button _resetButton;
  
  TextureManager* _textureManager;
  FontManager* _fontManager;

  //available coins
  PanelPions _panelPions;

  // Choosen coins (on screen)
  std::vector<PionDrawable> _pionsDChoosen;
  std::vector<Pion> _pionsChoosen;

  int _indexNextPion;
  
  sf::RectangleShape _backgroundChoosenCoins;

  std::vector<Pion> _pionValidated;
  ////////////////////////////
};

#endif

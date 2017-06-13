#include "PlateauDrawable.hpp"

PlateauDrawable::PlateauDrawable(TextureManager* text) :
  _textureManager(text), _panelPions(_textureManager),
  _backgroundChoosenCoins(sf::Vector2f(281,70))
{
  //available coins
  _panelPions.setPosition(sf::Vector2f(877,500));

  //choosen coins /////////////////////
  _backgroundChoosenCoins.setPosition(sf::Vector2f(400,690));

  indexNextPion = 0;

  for(int i = 0; i < 4; i++)
    {
      _pionsDChoosen.push_back(PionDrawable({Couleur::vide},_textureManager));
      _pionsChoosen.push_back({Couleur::vide});
    }

  for(int i = 0; i < 4; i++)
    _pionsDChoosen[i].setPosition(sf::Vector2f(404 + (i * 68),694));
  /////////////////////////////////////
}

void PlateauDrawable::catchEvent(sf::Event& event)
{
  Pion p(_panelPions.catchEvent(event));
  if(p.getCouleur() != Couleur::vide)
    {
      if(indexNextPion < 4)
	{
	  _pionsDChoosen[indexNextPion].setPion(p);
	  _pionsChoosen[indexNextPion] = p;
	  indexNextPion++;
	}
    }
}

void PlateauDrawable::setPosition(const sf::Vector2f& pos)
{}

void PlateauDrawable::draw(sf::RenderTarget& target, sf::RenderStates states)
  const
{
  target.draw(_panelPions,states);
  target.draw(_backgroundChoosenCoins,states);

  for(PionDrawable p : _pionsDChoosen)
    target.draw(p,states);
}

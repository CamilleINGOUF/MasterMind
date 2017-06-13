#include "PlateauDrawable.hpp"

#include <algorithm>

PlateauDrawable::PlateauDrawable(TextureManager* text, FontManager* font) :
  _textureManager(text),_fontManager(font), _panelPions(_textureManager),
  _backgroundChoosenCoins(sf::Vector2f(281,70)),
  _resetButton(_fontManager, "Reset"),_validateButton(_fontManager, "Valider")
{
  //available coins
  _panelPions.setPosition(sf::Vector2f(877,500));

  //choosen coins /////////////////////
  _backgroundChoosenCoins.setPosition(sf::Vector2f(400,690));

  _indexNextPion = 0;
  _resetButton.setPosition(sf::Vector2f(890,450));
  _resetButton.setCallback([this]()
			   {
			     reset();
			   });

  _validateButton.setPosition(sf::Vector2f(690,710));
  _validateButton.setCallback([this]()
			   {
			     validateCombi();
			   });

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
      if(_indexNextPion < 4 &&
	 !(std::find(_pionsChoosen.begin(), _pionsChoosen.end(), p)
	   != _pionsChoosen.end()))
	{
	  _pionsDChoosen[_indexNextPion].setPion(p);
	  _pionsChoosen[_indexNextPion] = p;
	  _indexNextPion++;
	}
    }
  _resetButton.catchEvent(event);
  _validateButton.catchEvent(event);
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

  target.draw(_resetButton,states);
  target.draw(_validateButton,states);
}

void PlateauDrawable::reset()
{
  _indexNextPion = 0;
  for(int i = 0; i < 4; i++)
    {
      _pionsDChoosen[i].setPion({Couleur::vide});
      _pionsChoosen[i].setCouleur(Couleur::vide);
    }
}

void PlateauDrawable::validateCombi()
{
  if(!(std::find(_pionsChoosen.begin(), _pionsChoosen.end(), Pion({Couleur::vide}))
       != _pionsChoosen.end()))
    {
      _pionValidated = _pionsChoosen;
      reset();
    }
}


std::vector<Pion> PlateauDrawable::getValidatedCombi()
{
  std::vector<Pion> tmp = _pionValidated;
  _pionValidated = {{Couleur::vide},{Couleur::vide},{Couleur::vide},{Couleur::vide}};
  return tmp;
}

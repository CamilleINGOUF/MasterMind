#include "PanelPions.hpp"

#include <iostream>
PanelPions::PanelPions() :
  _pions({rouge,jaune,marron,bleu,blanc,noir,vert,orange}),
  _rectangle(sf::Vector2f(140,260))
{
  
  _rectangle.setFillColor(sf::Color::White);
}

void PanelPions::catchEvent(sf::Event& event)
{
  
  for(PionDrawable p : _pionsD)
    {
      if(p.catchEvent(event))
	std::cout << (*p.getPion().getString()) << std::endl;
    }
}

void PanelPions::setPosition(const sf::Vector2f& pos)
{
  _rectangle.setPosition(pos);
  setPositionPions();
}

void PanelPions::setTextureManager(TextureManager* text)
{
  _textureManager = text;
  for(Pion pion : _pions)
    {
      _pionsD.push_back(PionDrawable(pion,text));
    }
  setPositionPions();
}

void PanelPions::setPositionPions()
{
  

  for(int i = 0; i < _pionsD.size(); i++)
    {
      if(i % 2 == 0)
	{
	  _pionsD[i].setPosition(sf::Vector2f(_rectangle.getPosition().x + 4,
					      _rectangle.getPosition().y + 4 +
					      (i * 32)));
	}
      else
	{
	  _pionsD[i].setPosition(sf::Vector2f(_rectangle.getPosition().x + 72,
					      _rectangle.getPosition().y + 4 +
					      ((i-1) * 32)));
	}
    }
}

void PanelPions::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_rectangle,states);
  for(PionDrawable p : _pionsD)
    target.draw(p);
}

#include "PanelPions.hpp"

PanelPions::PanelPions() :
  _pions({rouge,jaune,marron,bleu,blanc,noir,vert,orange}),
  _rectangle(sf::Vector2f(140,260))
{
  
  _rectangle.setFillColor(sf::Color::White);
}

Pion PanelPions::catchEvent(sf::Event& event)
{}

void PanelPions::setPosition(const sf::Vector2f& pos)
{
  _rectangle.setPosition(pos);
}

void PanelPions::setScale(const sf::Vector2f& factors)
{}

void PanelPions::setTextureManager(TextureManager* text)
{
  _textureManager = text;
  for(Pion pion : _pions)
    _pionsD.push_back(PionDrawable(pion,_textureManager));
}

void PanelPions::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_rectangle,states);
  for(int i = 0; i < _pionsD.size(); i++)
    {
      //TODO afficher les pions dans le panel
      if(i % 2 == 0)
	{

	}
      else
	{
	  
	}
      target.draw(_pionsD[i]);
    }
}

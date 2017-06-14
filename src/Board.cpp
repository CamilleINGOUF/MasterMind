////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "Board.hpp"

#include <algorithm>
#include <sstream>

////////////////////////////////////////////////////////////
Board::Board(TextureManager* text, FontManager* font) :
  _textureManager(text),
  _fontManager(font),
  _panelPions(_textureManager),
  _backgroundChoosenCoins(sf::Vector2f(212,56)),
  _resetButton(_fontManager, "Reset")
{

  _panelPions.setPosition(sf::Vector2f(877,500));
  _backgroundChoosenCoins.setPosition(sf::Vector2f(436,690));

  _indexNextPion = 0;
  _resetButton.setPosition(sf::Vector2f(890,450));
  _resetButton.setCallback([this]() {
      reset();
    });
  
  for (int i = 0; i < 4; i++)
  {
    _pionsDChoosen.push_back(PionDrawable({Couleur::vide},_textureManager));
    _pionsChoosen.push_back({Couleur::vide});
  }

  for (int i = 0; i < 4; i++)
    _pionsDChoosen[i].setPosition(sf::Vector2f(440 + (i * 48),694));

  int indexX = 0;
  int indexY = 0;
  for(int i = 0; i < 48; i++)
    {
      _correctionsD.push_back(CorrectionDrawable({Couleur::vide},_textureManager));
      _correctionsD[i].setPosition(sf::Vector2f(indexX*20 + 270,indexY*48 + 50));
      
      _combinaisonsD.push_back(PionDrawable({Couleur::vide},_textureManager));
      
      _combinaisonsD[i].setPosition(sf::Vector2f(indexX*48 + 440,indexY*48 + 50));

      
      if(indexX == 3)
	{
	  indexX = 0;
	  indexY++;
	}
      else
	indexX++;
    }
  
}


////////////////////////////////////////////////////////////
void Board::catchEvent(sf::Event& event)
{
  Pion p(_panelPions.catchEvent(event));

  if (p.getCouleur() != Couleur::vide)
  {
    if (_indexNextPion < 4 &&
       !(std::find(_pionsChoosen.begin(), _pionsChoosen.end(), p)
	 != _pionsChoosen.end()))
      {
	_pionsDChoosen[_indexNextPion].setPion(p);
	_pionsChoosen[_indexNextPion] = p;
	_indexNextPion++;
      }
  }
  
  _resetButton.catchEvent(event);
}


////////////////////////////////////////////////////////////
void Board::setPosition(const sf::Vector2f& pos)
{}


////////////////////////////////////////////////////////////
void Board::draw(sf::RenderTarget& target, sf::RenderStates states)
  const
{
  target.draw(_panelPions,states);
  target.draw(_backgroundChoosenCoins,states);

  for(PionDrawable p : _pionsDChoosen)
    target.draw(p,states);

  target.draw(_resetButton,states);

  for(int i = 0; i < 48; i++)
    {
      target.draw(_correctionsD[i],states);
      target.draw(_combinaisonsD[i],states);
    }
}


////////////////////////////////////////////////////////////
void Board::reset()
{
  _indexNextPion = 0;

  for (int i = 0; i < 4; i++)
  {
    _pionsDChoosen[i].setPion({Couleur::vide});
    _pionsChoosen[i].setCouleur(Couleur::vide);
  }
}


////////////////////////////////////////////////////////////
void Board::validateCombi()
{
  if(!(std::find(_pionsChoosen.begin(), _pionsChoosen.end(),
		 Pion({Couleur::vide})) != _pionsChoosen.end()))
  {
    _pionValidated = _pionsChoosen;
    reset();
  }
}


////////////////////////////////////////////////////////////
const std::string Board::getValidatedCombi()
{
  std::vector<Pion> tmp = _pionValidated;
  _pionValidated = {{Couleur::vide},{Couleur::vide},
		    {Couleur::vide},{Couleur::vide}};
  Combinaison combi(tmp);
  return combi.toString();
}



bool Board::doBoard(std::string board)
{
  std::cout << "Board.cpp->doBoard data : " << board << std::endl;
  std::istringstream std(board);
  std::string line;
  int indexComb = 0;
  int indexCorr = 0;
  while(std::getline(std, line))
    {
      for(unsigned i = 0; i < line.length(); i++)
	{
	  if(isValid(line[i]))
	    {
	      if(i < 4)
		//correction
		{
		  if(line[i] == 'B')
		    _correctionsD[indexCorr].setPion({blanc});
		  else if(line[i] == 'n')
		    _correctionsD[indexCorr].setPion({noir});
		  indexCorr++;
		}
	      else if(i > 4)
		//combinaison
		{
		  //std::cout << "Board.cpp->doBoard indexComb : " << indexComb << std::endl;
		  if(line[i] == 'B')
		    _combinaisonsD[indexComb].setPion({blanc});
		  else if(line[i] == 'n')
		    _combinaisonsD[indexComb].setPion({noir});
		  else if(line[i] == 'b')
		    _combinaisonsD[indexComb].setPion({bleu});
		  else if(line[i] == 'r')
		    _combinaisonsD[indexComb].setPion({rouge});
		  else if(line[i] == 'j')
		    _combinaisonsD[indexComb].setPion({jaune});
		  else if(line[i] == 'm')
		    _combinaisonsD[indexComb].setPion({marron});
		  else if(line[i] == 'o')
		    _combinaisonsD[indexComb].setPion({orange});
		  else if(line[i] == 'v')
		    _combinaisonsD[indexComb].setPion({vert});
		  indexComb++;
		}
	    }
	  else
	    {
	      empty();
	      return false;
	    }
	}
    }
  std::cout << "Board.cpp->doBoard out" << std::endl;
  return true;
}

bool Board::isValid(char ch)
{
  return ch == 'b' or ch == 'B' or ch == 'r' or ch == 'v' or
    ch == 'm' or ch == 'o' or ch == 'j' or ch == 'n' or
    ch == '.' or ch == ' ';
}

void Board::empty()
{
  for(int i = 0; i < 48; i++)
    {
      _correctionsD[i].setPion({vide});
      _combinaisonsD[i].setPion({vide});
    }
}

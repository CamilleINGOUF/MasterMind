#include "Combinaison.hpp"

#include <string>

Combinaison::Combinaison(): _pions({blanc, noir, bleu, rouge}){}

Combinaison::Combinaison(std::vector<Pion> pions): _pions(pions){}

Combinaison::~Combinaison(){}

std::vector<Pion> Combinaison::getPions() const
{
  return _pions;
}

void Combinaison::setPions(const std::vector<Pion> pions)
{
  _pions = pions;
}

void Combinaison::setPions(const std::string str)
{
  std::vector<Pion> p;
  for(std::string::size_type i = 0; i < str.size(); i++)
    {
      if(i >= 8) break;
      if(str[i] == 'r') p.push_back(rouge);
      if(str[i] == 'v') p.push_back(vert);
      if(str[i] == 'b') p.push_back(bleu);
      if(str[i] == 'm') p.push_back(marron);
      if(str[i] == 'o') p.push_back(orange);
      if(str[i] == 'j') p.push_back(jaune);
      if(str[i] == 'n') p.push_back(noir);
      if(str[i] == 'B') p.push_back(blanc);
      if(str[i] == '\n') break;
    }

  setPions(p);
}

bool Combinaison::operator==(Combinaison & that)
{
   bool toReturn = true;
  for(int i = 0; i < that._pions.size(); i++)
    {
      if(!(that._pions[i] == _pions[i]))
	toReturn = false;
    }
    return toReturn;
}

Combinaison & Combinaison::operator=(const Combinaison & c) {
    if (this != &c)
      {
	//std::cout << c << std::endl;
	_pions = c._pions;
      }
    return *this;
}

std::istream& operator >>(std::istream& is, Combinaison& c)
{

  std::locale vieuxLoc = std::locale::global(std::locale("fr_FR.UTF-8"));  

  Pion p;
  std::vector<Pion> pions;
  
  //is.ignore();

  while(is >> p)
    {
      //std::cout << "Pion : "<< p << std::endl;
      
      pions.push_back(p);
      if(is.get() == '\n')
	break;
    }
  c.setPions(pions);
  
  std::locale::global(vieuxLoc);
  return is;
}

std::ostream& operator <<(std::ostream& os, const Combinaison& c)
{
	std::locale vieuxLoc = std::locale::global(std::locale("fr_FR.UTF-8"));

	std::vector<char> pionsChar;
	
	for(int i = 0; i < 4; i++)
	  {
	    if(c.getPions()[i].getCouleur() == blanc) pionsChar.push_back('B');
	    if(c.getPions()[i].getCouleur() == bleu) pionsChar.push_back('b');
	    if(c.getPions()[i].getCouleur() == marron) pionsChar.push_back('m');
	    if(c.getPions()[i].getCouleur() == rouge) pionsChar.push_back('r');
	    if(c.getPions()[i].getCouleur() == vert) pionsChar.push_back('v');
	    if(c.getPions()[i].getCouleur() == orange) pionsChar.push_back('o');
	    if(c.getPions()[i].getCouleur() == jaune) pionsChar.push_back('j');
	    if(c.getPions()[i].getCouleur() == noir) pionsChar.push_back('n');
	  }
	
	os << pionsChar[0] << " "
	   << pionsChar[1] << " "
	   << pionsChar[2] << " "
	   << pionsChar[3] << std::endl;
	
	std::locale::global(vieuxLoc);
	return os;
}

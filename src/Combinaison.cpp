////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Combinaison.hpp"
#include <string>
#include <sstream>


////////////////////////////////////////////////////////////
Combinaison::Combinaison() :
  _pions({blanc, noir, bleu, rouge})
{
}


////////////////////////////////////////////////////////////
Combinaison::Combinaison(std::vector<Pion> pions) :
  _pions(pions)
{
}


////////////////////////////////////////////////////////////
Combinaison::~Combinaison()
{
}


////////////////////////////////////////////////////////////
std::vector<Pion> Combinaison::getPions() const
{
  return _pions;
}


////////////////////////////////////////////////////////////
void Combinaison::setPions(const std::vector<Pion> pions)
{
  _pions = pions;
}


////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////
bool Combinaison::operator==(Combinaison & that)
{
  bool toReturn = true;
  for(unsigned i = 0; i < that._pions.size(); i++)
  {
      if(!(that._pions[i] == _pions[i]))
	toReturn = false;
  }
  return toReturn;
}


////////////////////////////////////////////////////////////
Combinaison & Combinaison::operator=(const Combinaison & c) {
    if (this != &c)
    {
      //std::cout << c << std::endl;
      _pions = c._pions;
    }
    return *this;
 }


////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////
std::ostream& operator <<(std::ostream& os, const Combinaison& c)
{
  return os << c.toString();
}


////////////////////////////////////////////////////////////
const std::string Combinaison::toString() const
{
  std::stringstream sstream;
  
  for(int i = 0; i < 4; i++)
  {
    if(getPions()[i].getCouleur() == blanc) sstream << 'B';
    if(getPions()[i].getCouleur() == bleu) sstream << 'b';
    if(getPions()[i].getCouleur() == marron) sstream << 'm';
    if(getPions()[i].getCouleur() == rouge) sstream << 'r';
    if(getPions()[i].getCouleur() == vert) sstream << 'v';
    if(getPions()[i].getCouleur() == orange) sstream << 'o';
    if(getPions()[i].getCouleur() == jaune) sstream << 'j';
    if(getPions()[i].getCouleur() == noir) sstream << 'n';
  }

  return sstream.str();
}

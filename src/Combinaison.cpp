////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Combinaison.hpp"
#include <string>
#include <sstream>
#include <algorithm>

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
  _pions.clear();
  
  for(std::string::size_type i = 0; i < str.size(); i++)
  {
    if(i >= 8) break;
    if(str[i] == 'r') _pions.push_back(rouge);
    if(str[i] == 'v') _pions.push_back(vert);
    if(str[i] == 'b') _pions.push_back(bleu);
    if(str[i] == 'm') _pions.push_back(marron);
    if(str[i] == 'o') _pions.push_back(orange);
    if(str[i] == 'j') _pions.push_back(jaune);
    if(str[i] == 'n') _pions.push_back(noir);
    if(str[i] == 'B') _pions.push_back(blanc);
    if(str[i] == '\n') break;
  }
}


////////////////////////////////////////////////////////////
bool Combinaison::operator==(const Combinaison & that) const
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
    if(_pions[i].getCouleur() == blanc) sstream << 'B';
    if(_pions[i].getCouleur() == bleu) sstream << 'b';
    if(_pions[i].getCouleur() == marron) sstream << 'm';
    if(_pions[i].getCouleur() == rouge) sstream << 'r';
    if(_pions[i].getCouleur() == vert) sstream << 'v';
    if(_pions[i].getCouleur() == orange) sstream << 'o';
    if(_pions[i].getCouleur() == jaune) sstream << 'j';
    if(_pions[i].getCouleur() == noir) sstream << 'n';
    if(_pions[i].getCouleur() == vide) sstream << '.';
  }

  return sstream.str();
}


////////////////////////////////////////////////////////////
bool Combinaison::priv_isValid(const std::string& input)
{
  if (input.empty())
  {
    std::cout << "La combinaison ne peut être vide !" << std::endl;
    return false;
  }

  if (input.size() != 4)
  {
    std::cout << "La combinaison doit être composée de 4 lettres !" << std::endl;
    return false;
  }

  std::vector<char> lettres;
  
  for (std::string::size_type i = 0; i < input.size(); i++)
  {
    char carac = input[i];
    
    if (!Combinaison::isColor(carac))
    {
      std::cout << carac << " n'est pas une couleur !" << std::endl;
      return false;
    }
      
    if (std::find(lettres.begin(), lettres.end(), carac) != lettres.end())
    {
      std::cout << "Doublons non autorisés !" << std::endl;
      return false;
    }
    
    lettres.push_back(carac);
  }
  
  return true;
}


////////////////////////////////////////////////////////////
Combinaison Combinaison::fromInput()
{
  std::string input;

  do
  {
    std::cout << "Saisir une combinaison: ";
    std::getline(std::cin, input);
  }
  while (!Combinaison::priv_isValid(input));

  Combinaison combi;
  combi.setPions(input);
  return combi;
}


////////////////////////////////////////////////////////////
bool Combinaison::isColor(const char c)
{ 
  return c == 'r' or c == 'v' or c == 'b' or c == 'm' or c == 'o' or
    c == 'j' or c == 'n' or c == 'B';
}


////////////////////////////////////////////////////////////
bool Combinaison::pionDansLaCombinaison(Pion p)
{
  return (std::find(_pions.begin(), _pions.end(), p) != _pions.end());
}

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Plateau.hpp"

#include <sstream>
#include <stdexcept>
#include <cassert>


////////////////////////////////////////////////////////////
Plateau::Plateau()
{
  
}


////////////////////////////////////////////////////////////
Plateau::Plateau(std::vector<Combinaison>& combinaisons) :
  _combinaisons(combinaisons)
{
}


////////////////////////////////////////////////////////////
Plateau::~Plateau()
{
}


////////////////////////////////////////////////////////////
std::vector<Combinaison>& Plateau::getCombinaisons()
{
  return _combinaisons;
}


////////////////////////////////////////////////////////////
void Plateau::setCombinaisons(const std::vector<Combinaison> combinaisons)
{
  _combinaisons = combinaisons;
}

///////////////////////////////////////////////////////////
std::vector<Combinaison>& Plateau::getCorrections()
{
  return _corrections;
}

///////////////////////////////////////////////////////////
void Plateau::setCorrection(const std::vector<Combinaison> combinaisons)
{
  _corrections = combinaisons;
}


////////////////////////////////////////////////////////////
Combinaison Plateau::getLastCombinaison() const
{
  assert(_combinaisons.size() > 0);
  return _combinaisons.front(); 
}

////////////////////////////////////////////////////////////
void Plateau::addCombinaison(const Combinaison combinaison)
{

  if (_combinaisons.size() < 12)
    _combinaisons.insert(_combinaisons.begin(),combinaison);
}


////////////////////////////////////////////////////////////
void Plateau::addCorrection(const Combinaison combinaison)
{

  if (_corrections.size() < 12)
    _corrections.insert(_corrections.begin(),combinaison);
}


////////////////////////////////////////////////////////////
const std::string Plateau::toString() const
{
  std::stringstream sstream;
  for (unsigned i = 0; i < (12 - _combinaisons.size()); i++)
  {
    for (int j = 0; j < 4; j++)
      sstream << ".";

    sstream << " ";
    
    for (int j = 0; j < 4; j++)
      sstream << ".";
    
    sstream << "\n";
  }
  
  for(unsigned i = 0; i < _combinaisons.size(); i++)
  {
    sstream << _corrections[i] << " " << _combinaisons[i] << "\n";
  }
  
  return sstream.str();
}


////////////////////////////////////////////////////////////
unsigned Plateau::getNbCombinaisons() const
{
  return _combinaisons.size();
}


////////////////////////////////////////////////////////////
Combinaison Plateau::getCorrection(unsigned index) const
{
  if (index >= _corrections.size())
    throw std::runtime_error("Invalid index " + index);

  return _corrections[index];
}


////////////////////////////////////////////////////////////
Combinaison Plateau::getCombinaison(unsigned index) const
{
  if (index >= _combinaisons.size())
    throw std::runtime_error("Invalid index " + index);

  return _combinaisons[index];
}

////////////////////////////////////////////////////////////
std::ostream & operator<<(std::ostream & os, const Plateau & p)
{
  for (unsigned i = 12; i < (12 - p.getNbCombinaisons()); i++)
  {
    for (int j = 0; j < 4; j++)
	std::cout << ".";

    std::cout << " ";

    for (int j = 0; j < 4; j++)
	std::cout << ".";
    
    std::cout << std::endl;
  }
  
  for (unsigned i = p.getNbCombinaisons() - 1; i > 0; i--) 
    os << p.getCorrection(i)  << " " << p.getCombinaison(i) << std::endl;
    
  return os;
}


////////////////////////////////////////////////////////////
std::istream & operator>>(std::istream & is,  Plateau & p)
{
  std::locale vieuxLoc = std::locale::global(std::locale("fr_FR.UTF-8"));  

  Combinaison c;
  std::vector<Combinaison> comb;

  while(is >> c)
  {
    //std::cout << "Pion : "<< p.getCouleur() << std::endl;  
    comb.push_back(c);
  }
  
  p.setCombinaisons(comb);
  
  std::locale::global(vieuxLoc);
  return is;
}

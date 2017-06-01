#include "Plateau.hpp"

Plateau::Plateau(){}

Plateau::Plateau(std::vector<Combinaison> combinaisons)
  : _combinaisons(combinaisons)
{}

Plateau::~Plateau()
{}

std::vector<Combinaison> Plateau::getCombinaisons() const
{
  return _combinaisons;
}

void Plateau::setCombinaisons(const std::vector<Combinaison> combinaisons)
{
  _combinaisons = combinaisons;
}

Combinaison Plateau::getLastCombinaison() const
{
  return _combinaisons.back();
}
  
void Plateau::addCombinaison(const Combinaison combinaison)
{
  if(_combinaisons.size() < 12)
    _combinaisons.push_back(combinaison);
}

std::ostream & operator<<(std::ostream & os, const Plateau & p)
{
  for(int i = 0; i < 12 - p.getCombinaisons().size(); i++)
    {
      for(int j = 0; j < 4; j++)
	{
	  std::cout << ". ";
	}
      std::cout << std::endl;
    }
  for(int i = 0; i < p.getCombinaisons().size(); i++)
    {
      //std::cout << i << std::endl;
      os << p.getCombinaisons()[i];
    }
  return os;
}

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

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

bool Combinaison::operator==(const Combinaison & that)
{
  bool toReturn = true;
  for(int i = 0; i < that._pions.size(); i++)
    {
      if(that._pions(i) != _pions(i))
	toReturn = false;
    }
  return toReturn;
}

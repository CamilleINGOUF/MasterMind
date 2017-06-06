////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Plateau.hpp"
#include <sstream>


////////////////////////////////////////////////////////////
Plateau::Plateau()
{
  
}


////////////////////////////////////////////////////////////
Plateau::Plateau(std::vector<Combinaison> combinaisons) :
  _combinaisons(combinaisons)
{
}


////////////////////////////////////////////////////////////
Plateau::~Plateau()
{
}


////////////////////////////////////////////////////////////
std::vector<Combinaison> Plateau::getCombinaisons() const
{
  return _combinaisons;
}


////////////////////////////////////////////////////////////
void Plateau::setCombinaisons(const std::vector<Combinaison> combinaisons)
{
  _combinaisons = combinaisons;
}

///////////////////////////////////////////////////////////
std::vector<Combinaison> Plateau::getCorrections() const
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
  // TODO: DANGER: -> à supprimer au plus vite
  // Comportement indéfini quand le vecteur est vide !!!!
  return _combinaisons.back(); 
}

////////////////////////////////////////////////////////////
//dans le cli, la combinaison la plus récente se trouvera en bas du plateau
void Plateau::addCombinaison(const Combinaison combinaison)
{
  if(_combinaisons.size() < 12)
    _combinaisons.push_back(combinaison);
}

////////////////////////////////////////////////////////////
//dans le cli, la corretion la plus récente se trouvera en bas du plateau
void Plateau::addCorrection(const Combinaison combinaison)
{
  if(_corrections.size() < 12)
  {
    _corrections.push_back(combinaison);
  }
}


////////////////////////////////////////////////////////////
const std::string Plateau::toString() const
{
  std::stringstream sstream;
  for (unsigned i = 0; i < (12 - getCombinaisons().size()); i++)
  {
    for (int j = 0; j < 4; j++)
      sstream << ".";

    sstream << " ";
    
    for (int j = 0; j < 4; j++)
      sstream << ".";
    
    sstream << "\n";
  }
  
  for(unsigned i = 0; i < getCombinaisons().size(); i++)
  {
    sstream << getCorrections()[i] << " " << getCombinaisons()[i] << "\n";
  }
  
  return sstream.str();
}


////////////////////////////////////////////////////////////
std::ostream & operator<<(std::ostream & os, const Plateau & p)
{
  for (unsigned i = 0; i < (12 - p.getCombinaisons().size()); i++)
  {
    for (int j = 0; j < 4; j++)
	std::cout << ".";

    std::cout << " ";

    for (int j = 0; j < 4; j++)
	std::cout << ".";
    
    std::cout << std::endl;
  }
  
  for(unsigned i = 0; i < p.getCombinaisons().size(); i++) 
   os << p.getCorrections()[i]  << " " << p.getCombinaisons()[i] << std::endl;
    
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

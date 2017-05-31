/////////////////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////////////////

#include "Pion.hpp"
#include <locale>
#include <string>

Pion::Pion() : _couleur(blanc){}

Pion::Pion(Couleur couleur) : _couleur(couleur){}

Pion::~Pion(){}

Couleur Pion::getCouleur() const
{
  return _couleur;
}

void Pion::setCouleur(const Couleur couleur)
{
  _couleur = couleur;
}

bool Pion::operator==(const Pion & p2)
{
  return p2._couleur == _couleur;
}

std::istream& operator >>(std::istream& is, Pion& p) {

  std::locale vieuxLoc = std::locale::global(std::locale("fr_FR.UTF-8"));

  std::string buffer;
  if(std::getline(is,buffer,' '))
    {
      if(buffer == "r") p.setCouleur(rouge);
      if(buffer == "v") p.setCouleur(vert);
      if(buffer == "b") p.setCouleur(bleu);
      if(buffer == "m") p.setCouleur(marron);
      if(buffer == "o") p.setCouleur(orange);
      if(buffer == "j") p.setCouleur(jaune);
      if(buffer == "n") p.setCouleur(noir);
      if(buffer == "B") p.setCouleur(blanc);
    }
  
  std::locale::global(vieuxLoc);
  return is;
}

std::ostream& operator <<(std::ostream& os, const Pion& p) {
	std::locale vieuxLoc = std::locale::global(std::locale("fr_FR.UTF-8"));
	os << p.getCouleur() << " "; 
	std::locale::global(vieuxLoc);
	return os;
}

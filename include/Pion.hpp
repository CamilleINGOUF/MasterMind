#ifndef PION_HPP
#define PION_HPP

#include <iostream>

enum Couleur
  {
    rouge,
    vert,
    bleu,
    marron,
    orange,
    jaune,
    noir,
    blanc
  };

class Pion
{
private:
  Couleur _couleur;
public:
  Pion();
  Pion(Couleur couleur);
  ~Pion();
  Couleur getCouleur() const;
  void setCouleur(const Couleur couleur);
};

std::istream & operator>>(std::istream & is, Pion & p);

std::ostream & operator<<(std::ostream & os, const Pion & p);

#endif

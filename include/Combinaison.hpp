#ifndef COMBINAISON_HPP_
#define COMBINAISON_HPP_

#include "Pion.hpp"
#include <vector>

class Combinaison
{  
private:
  std::vector<Pion> _pions;
public:
  Combinaison();
  Combinaison(std::vector<Pion> pions);
  ~Combinaison();

  std::vector<Pion> getPions() const;
  void setPions(const std::vector<Pion> pions);

  bool operator==(Combinaison & that);
   Combinaison & operator=(const Combinaison & c);
};

std::ostream & operator<<(std::ostream & os, const Combinaison & c);
std::istream & operator>>(std::istream & is,  Combinaison & c);

#endif

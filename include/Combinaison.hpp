#ifndef COMBINAISON_HPP_
#define COMBINAISON_HPP_

#include "Pion.hpp"
#include <vector>
#include <string>

class Combinaison
{  
private:
  std::vector<Pion> _pions;
public:
  Combinaison();
  //Combinaison(std::string str);
  Combinaison(std::vector<Pion> pions);
  ~Combinaison();

  std::vector<Pion> getPions() const;
  void setPions(const std::vector<Pion> pions);

  void setPions(const std::string str);

  bool operator==(Combinaison & that);
   Combinaison & operator=(const Combinaison & c);
};

std::ostream & operator<<(std::ostream & os, const Combinaison & c);
std::istream & operator>>(std::istream & is,  Combinaison & c);

#endif

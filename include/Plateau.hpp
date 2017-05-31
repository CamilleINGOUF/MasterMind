#ifndef PLATEAU_HPP_
#define PLATEAU_HPP_

#include <vector>
#include "Combinaison.hpp"

class Plateau
{
private:
  std::vector<Combinaison> _combinaisons;
public:
  Plateau();
  Plateau(std::vector<Combinaison>);
  ~Plateau();

  std::vector<Combinaison> getCombinaisons() const;
  void setCombinaisons(const std::vector<Combinaison> combinaisons);

  Combinaison getLastCombinaison() const;
  void addCombinaison(const Combinaison combinaison);
};

std::ostream & operator<<(std::ostream & os, const Plateau & p);
std::istream & operator>>(std::istream & is,  Plateau & p);

#endif

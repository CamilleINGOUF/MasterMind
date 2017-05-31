#include "mastermind.hpp"
#include "Plateau.hpp"

int main()
{
  //MasterMind mm;
  //mm.run();

  Combinaison c;
  Combinaison c1;
  Combinaison c2;
  std::cin >> c;
  std::cin >> c1;
  std::cin >> c2;

  Plateau p({c,c1,c2});
  
  p.setCombinaisons({c,c1,c2});
  std::cout << "\n" << p << std::endl;
  
  return 0;
}

#include "mastermind.hpp"

int main()
{
  Mastermind mm;
  std::string pseudo;
  Combinaison codeSecret;
  Combinaison codeAjouter;
  
  std::cout << "Donner votre nom : ";
  std::cin >> pseudo;
  
  std::cout << "Vous êtes le codeur, créer un code secret : ";
  std::cin >> codeSecret;

  mm.setCodeSecret(codeSecret);
  mm.setNomJoueurServeur(pseudo);
  std::cout << "Code secret : " << mm.getCodeSecret() << std::endl;

  Combinaison c({blanc,bleu,orange,marron});
  Combinaison c2({jaune,vert,rouge,noir});

  Plateau p({c,c2});

  mm.setPlateau(p);
  std::cout << mm.getPlateau() << std::endl;

  std::cout << "Combinaison à ajouter : ";
  std::cin >> codeAjouter;
  
  return 0;
}

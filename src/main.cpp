#include "mastermind.hpp"

int main()
{
  Mastermind mm;
  std::string pseudo;

  std::string codeSecretString;
  Combinaison codeSecret;
  
  std::cout << "Donner votre nom : ";
  std::cin >> pseudo;
  
  std::cout << "Vous êtes le codeur, créer un code secret : ";
  std::cin >> codeSecretString;
  codeSecret.setPions(codeSecretString);

  mm.setCodeSecret(codeSecret);
  mm.setNomJoueurServeur(pseudo);
  std::cout << "Code secret : " << mm.getCodeSecret() << std::endl;

  Combinaison c({blanc,bleu,orange,marron});
  Combinaison c2({jaune,vert,rouge,noir});

  Plateau p({c,c2});

  mm.setPlateau(p);
  std::cout << mm.getPlateau() << std::endl;

  //std::cin.ignore();

  
  Combinaison codeAjouter;
  std::string codeString;
  std::cout << "Combinaison à ajouter : ";
  std::cin >> codeString;
  codeAjouter.setPions(codeString);

  Plateau pTemp;
  pTemp = mm.getPlateau();
  pTemp.addCombinaison(codeAjouter);
  mm.setPlateau(pTemp);
  
  std::cout << mm.getPlateau() << std::endl;
  
  return 0;
}

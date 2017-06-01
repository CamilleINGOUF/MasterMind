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

  Plateau p;
  

  mm.setPlateau(p);
  std::cout << mm.getPlateau() << std::endl;

  //std::cin.ignore();

  
  Combinaison codeAjouter;
  std::string codeString;

  bool isRunning = true;

  mm.setScoreServeur(0);

  while(isRunning)
    {
      
      std::cout << "Combinaison à ajouter : ";
      std::cin >> codeString;
      codeAjouter.setPions(codeString);
      
      Plateau pTemp;
      pTemp = mm.getPlateau();
      pTemp.addCombinaison(codeAjouter);
      mm.setPlateau(pTemp);
  
      std::cout << mm.getPlateau() << std::endl;
      mm.setScoreServeur(mm.getScoreServeur() + 1);

      if(codeAjouter == mm.getCodeSecret())
	{
	  std::cout << "Gagné ! Avec "
		    << mm.getScoreServeur()
		    << " point(s)" << std::endl;
	  isRunning = false;
	}
      else if(mm.getPlateau().getCombinaisons().size() == 12)
	{
	  
	  mm.setScoreServeur(20);
	  std::cout << "Perdu ! Avec "
		    << mm.getScoreServeur()
		    << " point(s)" << std::endl;
	  isRunning = false;
	}
    }
  
  return 0;
}

#include "mastermind.hpp"

int main()
{
  Mastermind mm;
  std::string pseudo;
  int nombreManches;

  std::string codeSecretString;
  Combinaison codeSecret;
  
  std::cout << "Donner votre nom : ";
  std::cin >> pseudo;

  std::cout << "Nombre de manches : ";
  std::cin >> nombreManches;
  mm.setNbManches(nombreManches);
  
  std::cout << "Vous êtes le codeur, créer un code secret : ";
  std::cin >> codeSecretString;
  codeSecret.setPions(codeSecretString);

  mm.setCodeSecret(codeSecret);
  mm.setNomJoueurServeur(pseudo);
  std::cout << "Code secret : " << mm.getCodeSecret() << std::endl;

  
  Combinaison combinaisonAjouter;
  std::string combinaisonString;

  bool isOver = false;

  mm.setScoreServeur(0);

  std::cout << mm.getPlateau();
  
  while(!isOver)
    {
      std::cout << "Combinaison à ajouter : ";
      std::cin >> combinaisonString;
      combinaisonAjouter.setPions(combinaisonString);

      Plateau tempPlateau;
      tempPlateau = mm.getPlateau();
      tempPlateau.addCombinaison(combinaisonAjouter);
      mm.setPlateau(tempPlateau);
      
      mm.setScoreServeur(mm.getScoreServeur() + 1);

      std::cout << mm.getPlateau();

      if(mm.decodeurGagnant())
	{
	  //Gagné
	  std::cout << "Tu as gagné avec " << mm.getScoreServeur() << std::endl;
	  mm.inverserRoles();
	  std::cout << "On inverse les rôles mais tu es seul" << std::endl;
	}
      else if(mm.tourTermine())
	{
	  //Perdu
	  mm.setScoreServeur(mm.getScoreServeur() + 20);
	  std::cout << "Tu as perdu avec " << mm.getScoreServeur() << std::endl;
	  mm.inverserRoles();
	  std::cout << "On inverse les rôles mais tu es seul" << std::endl;
	}

      std::cout << "Manches : " << mm.getCurrentNbManches() << std::endl;
      isOver = mm.partieTerminee();
    }
  
  return 0;
}

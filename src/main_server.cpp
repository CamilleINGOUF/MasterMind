////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "Server.hpp"

#include <iostream>
#include <stdexcept>

////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
  // Vérification des arguments
  if (argc != 3)
  {
    std::cerr << "Utilisation: ./server.out <port> <nombre de manches>"
	      << std::endl;
    exit(-1);
  }

  // Saisie du port
  unsigned port(0);
  
  try
  {
    port = std::atoi(argv[1]);
  }
  catch (const std::invalid_argument& err)
  {
    std::cerr << "Le port n'est pas valide !" << std::endl;
    return -1;
  }
  catch (const std::out_of_range& err)
  {
    std::cerr << "Le port n'est pas valide !" << std::endl;
    return -1;
  }

  if (port <= 0)
  {
    std::cerr << "Le port n'est pas valide !" << std::endl;
    return -1;
  }

  // Saisie du nombre de manches
  int nbManches(0);
  
  try
  {
    nbManches = std::atoi(argv[2]);
  }
  catch (const std::invalid_argument& err)
  {
    std::cerr << "Le nombre de manches est invalide !" << std::endl;
    return -1;
  }
  catch (const std::out_of_range& err)
  {
    std::cerr << "Le nombre de manches est invalide !" << std::endl;
    return -1;
  }

  if (nbManches <= 0)
  {
    std::cerr << "Le nombre de manches ne peut être négatif !" << std::endl;
    return -1;
  }
  
  // Création et lancement du serveur
  try
  {
    Server serveur(port, nbManches);
    serveur.run();
  }
  catch (const std::exception& err)
  {
    std::cerr << err.what() << std::endl;
    return -1;
  }
  
  return 0;
}

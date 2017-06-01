////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "server.hpp"
#include "Plateau.hpp"
#include <iostream>
#include <stdlib.h>


////////////////////////////////////////////////////////////
Server::Server(unsigned port) :
  _port(port),
  _pSocket(nullptr),
  _pListener(nullptr),
  _nbManches(0)
{

}


////////////////////////////////////////////////////////////
Server::~Server()
{
}


////////////////////////////////////////////////////////////
void Server::run()
{
  // Saisie du nombre de manches
  // TODO: check erreur (saisie incorrecte / <= 0)
  std::cout << "Nombre de manches: ";
  std::cin >> _nbManches;
  
  // Saisie du pseudo
  std::cout << "Pseudo: ";
  // TODO: check pseudo invalide ?
  std::cin >> _nameHost;

  // Affichage de l'IP du serveur
  sf::IpAddress localIP  = sf::IpAddress::getLocalAddress();
  sf::IpAddress publicIP = sf::IpAddress::getPublicAddress(sf::seconds(5));

  std::cout << "Adresse locale du serveur (" << localIP << ")" << std::endl;
  std::cout << "Adresse publique du serveur (" << publicIP << ")" << std::endl;
  
  // Écoute sur le port
  _pListener = std::make_unique<sf::TcpListener>();
  if (_pListener->listen(_port) != sf::Socket::Done)
  {
    throw std::string(" Impossible d'écouter sur le port: " + _port);
  }

  // En attente d'une connexion
  std::cout << "En attente de connexion..." << std::endl;
  _pSocket = std::make_unique<sf::TcpSocket>();

  if (_pListener->accept(*_pSocket) != sf::Socket::Done)
  {
    throw std::string("Impossible d'accepter une connexion");
  }

  std::cout << "Le client (" << _pSocket->getRemoteAddress().toString()
	    << ") a rejoint le serveur" << std::endl;

  // TODO: Check validité de la combinaison
  // Saisie de la combinaison
  std::cout << "Saisir la combinaison: " << std::endl;
  Combinaison combinaison;
  std::cin >> combinaison;

  // Envoi de la confirmation
  sf::Packet packet;
}

////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
  // Saisie du port
  if (argc != 2)
  {
    std::cerr << "Utilisation: ./server.out <port>" << std::endl;
    exit(-1);
  }
  
  unsigned port = atoi(argv[1]);
  Server serveur(port);

  try
  {
    serveur.run();
  }
  catch (const std::string& err)
  {
    std::cerr << err << std::endl;
  }
  
  return 0;
}

////////////////////////////////////////////////////////////
//
// Mastermind
// Copyright (C) 2017 - CAFA
//
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "server.hpp"
#include "Plateau.hpp"
#include "Combinaison.hpp"
#include "protocol.hpp"
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <SFML/Network.hpp>


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
  priv_getSettings();
  priv_initServer();

  // Tant que le nb de manches < nbTotal de manches
  // Si Codeur
  // Choisir le code secret
  // Attendre que le joueur trouve
  // Refresh affichage
  // Si Décodeur
  // Choisir une combinaison
  // Trouve ou pas
  // Refresh des affichages
  // Passe au tour / Manche suivante
  // Update des scores
  // Fin de la partie afficher le vainqueur
  // Fin du programme

  sf::Packet packet;
  sf::Socket::Status status;

  // Tant que toutes les manches n'ont pas été jouées
  while (!_game.partieTerminee())
  {
    // Début de partie
    if (_game.plateauVide())
    {
      // Attende de le confirmation du client
      if (_game.getDecodeur() == Client)
      {
	if (_pSocket->receive(packet) != sf::Socket::Done)
	{
	  throw std::string("Server::run() - Impossible de recevoir la confirmation du client");
	}

	std::string codeSecret;
	
	if (!(packet >> codeSecret))
	  throw std::string("Server::run() - erreur à la réception du paquet");

	Combinaison combinaison;
	combinaison.setPions(codeSecret);
	_game.setCodeSecret(combinaison);
      }
      // Saisie locale
      else
      {
	Combinaison combinaison = Combinaison::fromInput();
	_game.setCodeSecret(combinaison);

	// Envoi de la confirmation
	packet.clear();
	packet << _nameHost << _game.getPlateau();

	status = _pSocket->send(packet);

	if (status != sf::Socket::Done)
	{
	  std::cout << "Le client s'est déconnecté !" << std::endl;
	  return;
	}
      }
    }
  }
}
  

////////////////////////////////////////////////////////////
void Server::priv_getSettings()
{
  // Saisie du nombre de manches
  std::string input;
  
  do
  {
    std::cout << "Nombre de manches: ";
    std::getline(std::cin, input);

    try
    {
      _nbManches = std::stoi(input);
    }
    catch (const std::invalid_argument& err)
    {
      continue;
    }
    catch (const std::out_of_range& err)
    {
      continue;
    }
  }
  while (input.empty() || _nbManches <= 0);
  
  
  // Saisie du pseudo
  do
  {
    std::cout << "Pseudo: ";
    std::getline(std::cin, _nameHost);
  }
  while (_nameHost.empty());  
}


////////////////////////////////////////////////////////////
void Server::priv_initServer()
{
  // Préparation du jeu
  _game.setNbManches(_nbManches);
  _game.setNomJoueurServeur(_nameHost);
  
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

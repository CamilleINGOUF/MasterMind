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
#include <iostream>
#include <stdlib.h>
#include <sstream>


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
  
  // TODO: Check validité de la combinaison
  // Saisie de la combinaison
  std::cout << "Saisir la combinaison: " << std::endl;
  Combinaison combinaison;
  std::cin >> combinaison;

  _game.setCodeSecret(combinaison);

  // Envoi de la confirmation (pseudo de l'hôte + plateau initial)
  sf::Packet packet;
  packet << _nameHost << _game.getPlateau();
  
  if (_pSocket->send(packet) != sf::Socket::Done)
  {
    throw std::string("Impossible d'envoyer la confirmation");
  }

  std::cout << _game.getPlateau();

  // Attente de la combinaison du client
  packet.clear();

  if (_pSocket->receive(packet) != sf::Socket::Done)
  {
    throw std::string("Pas de réponse de la part du client");
  }
  
  // Réception
  std::string combi;
  if (packet >> combi)
  {
    combinaison.setPions(combi);
  }

  _game.getPlateau().addCombinaison(combinaison);

  // Refresh  
  packet.clear();
  packet << _game.getPlateau();

  if (_pSocket->send(packet) != sf::Socket::Done)
  {
    throw std::string("Impossible d'envoyer le plateau modifié");
  }

  std::cout << _game.getPlateau();
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
sf::Packet& operator<<(sf::Packet& pkt, const Plateau& p)
{
  return pkt << p.toString();
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

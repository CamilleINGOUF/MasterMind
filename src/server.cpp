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

    if (input.empty())
      std::cerr << "Le nombre de manches ne peut être vide !" << std::endl;

    if (_nbManches <= 0)
      std::cerr << "Le nombre de manches doit être positif !" << std::endl;
  }
  while (input.empty() || _nbManches <= 0);
  
  
  // Saisie du pseudo
  do
  {
    std::cout << "Pseudo: ";
    std::getline(std::cin, _nameHost);

    if (_nameHost.empty())
      std::cerr << "Votre nom ne peut être vide !" << std::endl;
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
    throw std::string(" Impossible d'écouter sur le port: " + _port);

  // En attente d'une connexion
  std::cout << "En attente de connexion..." << std::endl;
  _pSocket = std::make_unique<sf::TcpSocket>();

  if (_pListener->accept(*_pSocket) != sf::Socket::Done)
    throw std::string("Impossible d'accepter une connexion");
  
  std::cout << "Le client (" << _pSocket->getRemoteAddress().toString()
	    << ") a rejoint le serveur" << std::endl;

  // Envoi du pseudo de l'hôte
  sf::Packet packet;
  packet << _nameHost;

  if (_pSocket->send(packet) != sf::Socket::Done)
    throw std::string("Impossible d'envoyer le pseudo de l'hôte");

  // Réception du pseudo du client
  packet.clear();

  if (_pSocket->receive(packet) != sf::Socket::Done)
    throw std::string("Impossible de recevoir le pseudo du client");

  if (!(packet >> _nameClient))
    throw std::string("Erreur de paquet lors de la réception du nom du client");

  std::cout << "Vous jouer contre " <<_nameClient << " !" << std::endl;
}


////////////////////////////////////////////////////////////
void Server::priv_updateTour()
{
  sf::Packet packet;
  
  // Début de partie
  if (_game.plateauVide())
  {
    // Envoi de la confirmation au client
    if (_game.getDecodeur() == Client)
    {
      Combinaison combinaison = Combinaison::fromInput();
      _game.setCodeSecret(combinaison);

      packet << static_cast<sf::Int32>(PacketType::Confirmation);
      
      if (_pSocket->send(packet) != sf::Socket::Done)
	throw std::string("Impossible d'envoyer la confirmation de sélection de combinaison");
    }
    else
    {
      _game.setCodeSecret(priv_requestCombinaison(true));
    }
  }

  // Récupération de la combinaison
  if (_game.getDecodeur() == Client)
  {
    Combinaison combinaison = priv_requestCombinaison(false);
    _game.ajouterCombinaison(combinaison);
  }
  else
  {
    Combinaison combiServer = Combinaison::fromInput();
    _game.ajouterCombinaison(combiServer);
  }

  // Refresh de l'affichage
  std::cout << _game.getPlateau();  

  packet.clear();

  // Vérification + Mise à jour du jeu
  if (_game.tourTermine())
  {
    // Mise à jour des points
    if (_game.decodeurGagnant())
    {
      if (_game.getDecodeur() == Serveur)
	_game.ajoutPoints(Serveur, _game.getNombreEssais());
      else
	_game.ajoutPoints(Client, _game.getNombreEssais());
    }
    else
    {
      if (_game.getDecodeur() == Serveur)
	_game.ajoutPoints(Serveur, 20);
      else
	_game.ajoutPoints(Client, 20);
    }

    std::cout << "Scores:" << std::endl << _nameHost << ": "
	      << _game.getScoreServeur() << " points" << std::endl
	      << _nameClient << ": " << _game.getScoreClient()
	      << " points" << std::endl;

    // Envoi des informations de fin de tour
    packet << static_cast<sf::Int32>(PacketType::TurnFinished);

    if (_game.getDecodeur() == Serveur)
      packet << static_cast<sf::Int32>(_game.getScoreServeur());
    else
      packet << static_cast<sf::Int32>(_game.getScoreClient());

    packet << _game.getPlateau().toString();

    _game.inverserRoles();
    std::cout << "Inversion des rôles" << std::endl;
  }
  else
  {
    packet << static_cast<sf::Int32>(PacketType::TurnNotFinished)
	   << _game.getPlateau().toString();
  }

  if (_pSocket->send(packet) != sf::Socket::Done)
    throw std::string("Impossible d'envoyer le paquet de refresh !");
}


////////////////////////////////////////////////////////////
Combinaison Server::priv_requestCombinaison(bool combiSecrete)
{  
  // Requête d'une combinaison
  if (combiSecrete)
  {
    std::cout << "En attente d'une combinaison secrète de "
	      << _nameClient << "..." << std::endl;
  }
  else
  {     
    std::cout << "En attente d'une combinaison de "
	    << _nameClient << "..." << std::endl;
  }
  
  sf::Packet packet;
  packet << static_cast<sf::Int32>(PacketType::CombinaisonRequest);
  if (_pSocket->send(packet) != sf::Socket::Done)
    throw std::string("Impossible d'envoyer une requête de combinaison");
      
  // Réception de la combinaison
  packet.clear();
  if (_pSocket->receive(packet) != sf::Socket::Done)
    throw std::string("Impossible de recevoir une combinaison");

  // Extraction de la combinaison
  std::string combiStr;	
  if (!(packet >> combiStr))
    throw std::string("Erreur d'extraction de la combinaison !");

  Combinaison combinaison;
  combinaison.setPions(combiStr);

  return combinaison;
}


////////////////////////////////////////////////////////////
void Server::priv_mainLoop()
{
  while (!_game.partieTerminee())
  {
    while (!_game.mancheTerminee())
    {
      while (!_game.tourTermine())
      {
	priv_updateTour();
      }
    }
  }

  sf::Packet packet;
  packet << static_cast<sf::Int32>(PacketType::GameFinished);

  if (_pSocket->send(packet) != sf::Socket::Done)
    throw std::string("Impossible d'envoyer le paquet - PacketType::GameFinished");

  std::cout << "La partie est terminée !" << std::endl;
}


////////////////////////////////////////////////////////////
void Server::run()
{
  priv_getSettings();
  priv_initServer();
  priv_mainLoop();
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

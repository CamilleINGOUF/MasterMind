////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "protocol.hpp"
#include "Combinaison.hpp"
#include "Plateau.hpp"
#include "Server.hpp"
#include "Utils.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <SFML/Network.hpp>


////////////////////////////////////////////////////////////
Server::Server(unsigned port, unsigned nbManches) :
  _port(port)
{
  _game.setNbManches(nbManches);
}


////////////////////////////////////////////////////////////
Server::~Server()
{
}


////////////////////////////////////////////////////////////
void Server::init()
{  
  // Affichage de l'IP du serveur
  sf::IpAddress localIP  = sf::IpAddress::getLocalAddress();
  sf::IpAddress publicIP = sf::IpAddress::getPublicAddress(sf::seconds(5));

  std::cout << "Adresse locale du serveur (" << localIP << ")" << std::endl;
  std::cout << "Adresse publique du serveur (" << publicIP << ")" << std::endl;
  
  // Écoute sur le port
  if (_listener.listen(_port) != sf::Socket::Done)
    throw std::runtime_error(" Impossible d'écouter sur le port: " + _port);
  
  // En attente du joueur A
  std::cout << "En attente de connexion du joueur A" << std::endl;
 
  if (_listener.accept(_socketA) != sf::Socket::Done)
    throw std::runtime_error("Impossible d'accepter une connexion");
  
  std::cout << "Le client (" << _socketA.getRemoteAddress().toString()
	    << ") a rejoint le serveur" << std::endl;

  // Requête pour le pseudo du joueur A
  sf::Packet packet;
  packet << static_cast<sf::Int32>(ServerPacket::NameRequest);
  
  if (_socketA.send(packet) != sf::Socket::Done)
    throw std::runtime_error("Requête Pseudo - Joueur A Impossible");

  // Réception du pseudo du joueur A
  packet.clear();

  if (_socketA.receive(packet) != sf::Socket::Done)
    throw std::runtime_error("Impossible de recevoir le pseudo du joueur A");

  if (!(packet >> _nameA))
    throw std::runtime_error("Impossible de lire le pseudo du joueur A");

  std::cout << "Le client A (" << _nameA << ")" << std::endl;

  // En attente du joueur B
  std::cout << "En attente de connexion du joueur B" << std::endl;
 
  if (_listener.accept(_socketB) != sf::Socket::Done)
    throw std::runtime_error("Impossible d'accepter une connexion");
  
  std::cout << "Le client (" << _socketB.getRemoteAddress().toString()
	    << ") a rejoint le serveur" << std::endl;

  // Requête pour le pseudo du joueur B
  packet.clear();
  packet << static_cast<sf::Int32>(ServerPacket::NameRequest);
  
  if (_socketB.send(packet) != sf::Socket::Done)
    throw std::runtime_error("Requête Pseudo - Joueur B Impossible");

  // Réception du pseudo du joueur B
  packet.clear();

  if (_socketB.receive(packet) != sf::Socket::Done)
    throw std::runtime_error("Impossible de recevoir le pseudo du joueur A");

  if (!(packet >> _nameB))
    throw std::runtime_error("Impossible de lire le pseudo du joueur A");

  std::cout << "Le client B (" << _nameB << ")" << std::endl;

  // Message la partie va commencer
  packet.clear();
  packet << static_cast<sf::Int32>(ServerPacket::GameBegin);

  if (_socketA.send(packet) != sf::Socket::Done)
    throw std::runtime_error("Requête GameBegin - Impossible à envoyer");

  if (_socketB.send(packet) != sf::Socket::Done)
    throw std::runtime_error("Requête GameBegin - Impossible à envoyer");
}


////////////////////////////////////////////////////////////
void Server::updateTour()
{
  // sf::Packet packet;
  
  // // Début de partie
  // if (_game.plateauVide())
  // {
  //   // Envoi de la confirmation au client
  //   if (_game.getDecodeur() == Client)
  //   {
  //     Combinaison combinaison = Combinaison::fromInput();
  //     _game.setCodeSecret(combinaison);

  //     packet << static_cast<sf::Int32>(PacketType::Confirmation);
      
  //     if (_pSocket->send(packet) != sf::Socket::Done)
  // 	throw std::string("Impossible d'envoyer la confirmation de sélection de combinaison");
  //   }
  //   else
  //   {
  //     _game.setCodeSecret(priv_requestCombinaison(true));
  //   }
  // }

  // // Récupération de la combinaison
  // if (_game.getDecodeur() == Client)
  // {
  //   Combinaison combinaison = priv_requestCombinaison(false);
  //   _game.ajouterCombinaison(combinaison);
  // }
  // else
  // {
  //   Combinaison combiServer = Combinaison::fromInput();
  //   _game.ajouterCombinaison(combiServer);
  // }

  // _game.corrigerDerniereCombinaison();

  // // Refresh de l'affichage
  // std::cout << _game.getPlateau();  

  // packet.clear();

  // // Vérification + Mise à jour du jeu
  // if (_game.tourTermine())
  // {
  //   // Mise à jour des points
  //   if (_game.decodeurGagnant())
  //   {
  //     if (_game.getDecodeur() == Serveur)
  // 	_game.ajoutPoints(Serveur, _game.getNombreEssais());
  //     else
  // 	_game.ajoutPoints(Client, _game.getNombreEssais());
  //   }
  //   else
  //   {
  //     if (_game.getDecodeur() == Serveur)
  // 	_game.ajoutPoints(Serveur, 20);
  //     else
  // 	_game.ajoutPoints(Client, 20);
  //   }

  //   std::cout << "Scores:" << std::endl << _nameA << ": "
  // 	      << _game.getScoreServeur() << " points" << std::endl
  // 	      << _nameA << ": " << _game.getScoreClient()
  // 	      << " points" << std::endl;

  //   // Envoi des informations de fin de tour
  //   packet << static_cast<sf::Int32>(PacketType::TurnFinished);

  //   if (_game.getDecodeur() == Serveur)
  //     packet << static_cast<sf::Int32>(_game.getScoreServeur());
  //   else
  //     packet << static_cast<sf::Int32>(_game.getScoreClient());

  //   packet << _game.getPlateau().toString();

  //   _game.inverserRoles();
  //   std::cout << "Inversion des rôles" << std::endl;
  // }
  // else
  // {
  //   packet << static_cast<sf::Int32>(PacketType::TurnNotFinished)
  // 	   << _game.getPlateau().toString();
  // }

  // if (_pSocket->send(packet) != sf::Socket::Done)
  //   throw std::string("Impossible d'envoyer le paquet de refresh !");
}


////////////////////////////////////////////////////////////
Combinaison Server::requestCombinaison(bool combiSecrete)
{  
  // Requête d'une combinaison
  // if (combiSecrete)
  // {
  //   std::cout << "En attente d'une combinaison secrète de "
  // 	      << _nameA << "..." << std::endl;
  // }
  // else
  // {     
  //   std::cout << "En attente d'une combinaison de "
  // 	    << _nameA << "..." << std::endl;
  // }
  
  // sf::Packet packet;
  // packet << static_cast<sf::Int32>(PacketType::CombinaisonRequest);
  // if (_pSocket->send(packet) != sf::Socket::Done)
  //   throw std::string("Impossible d'envoyer une requête de combinaison");
      
  // // Réception de la combinaison
  // packet.clear();
  // if (_pSocket->receive(packet) != sf::Socket::Done)
  //   throw std::string("Impossible de recevoir une combinaison");

  // // Extraction de la combinaison
  // std::string combiStr;	
  // if (!(packet >> combiStr))
  //   throw std::string("Erreur d'extraction de la combinaison !");

  // Combinaison combinaison;
  // combinaison.setPions(combiStr);

  // return combinaison;
}


////////////////////////////////////////////////////////////
void Server::mainLoop()
{
  while (!_game.partieTerminee())
  {
    while (!_game.mancheTerminee())
    {
      while (!_game.tourTermine())
      {
  	updateTour();
      }
    }
  }

  // Fin de partie
  sf::Packet packet;
  packet << static_cast<sf::Int32>(ServerPacket::GameFinished);
  packet << _game.getGagnantNom();


  // Envoi de la notification aux clients
  if (_socketA.send(packet) != sf::Socket::Done)
    throw std::runtime_error("Impossible d'envoyer le paquet - PacketType::GameFinished");

  if (_socketB.send(packet) != sf::Socket::Done)
    throw std::runtime_error("Impossible d'envoyer le paquet - PacketType::GameFinished");


  std::cout << "Le gagnant est " << _game.getGagnantNom() << std::endl
  	    << "La partie est terminée !" << std::endl;
}


////////////////////////////////////////////////////////////
void Server::run()
{
  init();
  //mainLoop();
}

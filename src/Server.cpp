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

  _game.setNomJoueurA(_nameA);
  _game.setNomJoueurB(_nameB);


  // Envoi du pseudo de l'adversaire
  packet.clear();
  packet << static_cast<sf::Int32>(ServerPacket::GameBegin);
  packet << _nameB;
  
  if (_socketA.send(packet) != sf::Socket::Done)
    throw std::runtime_error("Impossible d'envoyer un pseudo au joueur A");

  packet.clear();
  
  packet << static_cast<sf::Int32>(ServerPacket::GameBegin);
  packet << _nameA;
  
  if (_socketB.send(packet) != sf::Socket::Done)
    throw std::runtime_error("Impossible d'envoyer un pseudo au joueur B");
}


////////////////////////////////////////////////////////////
void Server::updateTour()
{
  sf::Packet packet;
  
  // // Début de partie
  if (_game.plateauVide())
  {
    if (_game.getDecodeur() == Joueur::A)
    {
      Combinaison combi = requestCombinaison(Joueur::B, true);
      _game.setCodeSecret(combi);
      broadcastMessage(_nameB + " a choisit le code secret !");
    }
    else
    {
      Combinaison combi = requestCombinaison(Joueur::A, true);
      _game.setCodeSecret(combi);
      broadcastMessage(_nameA + " a choisit le code secret !");
    }
  }

  // Récupération de la combinaison
  if (_game.getDecodeur() == Joueur::A)
  {
    broadcastMessage("En attente de la combinaison de " + _nameA);
    Combinaison combinaison = requestCombinaison(Joueur::A, false);
    _game.ajouterCombinaison(combinaison);
  }
  else
  {
    broadcastMessage("En attente de la combinaison de " + _nameB);
    Combinaison combinaison = requestCombinaison(Joueur::B, false);
    _game.ajouterCombinaison(combinaison);
  }

  _game.corrigerDerniereCombinaison();

  // Refresh de l'affichage
  std::cout << _game.getPlateau();  

  // Vérification + Mise à jour du jeu
  if (_game.tourTermine())
  {
    // Mise à jour des points
    if (_game.decodeurGagnant())
    {
      if (_game.getDecodeur() == Joueur::A)
  	_game.ajoutPoints(Joueur::A, _game.getNombreEssais());
      else
  	_game.ajoutPoints(Joueur::B, _game.getNombreEssais());
    }
    // Le décodeur n'a pas trouvé le code secret 
    else 
    {
      if (_game.getDecodeur() == Joueur::A)
  	_game.ajoutPoints(Joueur::A, 20);
      else
  	_game.ajoutPoints(Joueur::B, 20);
    }

    std::cout << "Scores:" << std::endl << _nameA << ": "
  	      << _game.getScoreJoueurA() << " points" << std::endl
  	      << _nameB << ": " << _game.getScoreJoueurB()
  	      << " points" << std::endl;

    // Envoi des informations de fin de tour
    packet << static_cast<sf::Int32>(ServerPacket::TurnFinished)
	   << static_cast<sf::Int32>(_game.getScoreJoueurA())
	   << static_cast<sf::Int32>(_game.getScoreJoueurB())
	   << _game.getPlateau().toString();

    if (_socketA.send(packet) != sf::Socket::Done)
      throw std::runtime_error("Impossible d'envoyer le paquet de refresh !");

    packet.clear();

    packet << static_cast<sf::Int32>(ServerPacket::TurnFinished)
	   << static_cast<sf::Int32>(_game.getScoreJoueurB())
	   << static_cast<sf::Int32>(_game.getScoreJoueurA())
	   << _game.getPlateau().toString();
    
    if (_socketB.send(packet) != sf::Socket::Done)
      throw std::runtime_error("Impossible d'envoyer le paquet de refresh !");


    _game.inverserRoles();
    std::cout << "Inversion des rôles" << std::endl;
    return;
  }

  packet << static_cast<sf::Int32>(ServerPacket::TurnNotFinished)
	 << _game.getPlateau().toString();

  if (_socketA.send(packet) != sf::Socket::Done)
    throw std::runtime_error("Impossible d'envoyer le paquet de refresh !");

  
  if (_socketB.send(packet) != sf::Socket::Done)
    throw std::runtime_error("Impossible d'envoyer le paquet de refresh !");
}


////////////////////////////////////////////////////////////
Combinaison Server::requestCombinaison(Joueur joueur, bool combiSecrete)
{  
  // Log serveur
  if (combiSecrete)
  {
    std::cout << "En attente d'une combinaison secrète de ";
    
    if (joueur == Joueur::A)
      std::cout << _nameA << std::endl;
    else
      std::cout << _nameB << std::endl;
  }
  else
  {     
    std::cout << "En attente d'une combinaison de ";

    if (joueur == Joueur::A)
      std::cout << _nameA << std::endl;
    else
      std::cout << _nameB << std::endl;
  }

  // Envoi de la requête
  sf::Packet packet;
  packet << static_cast<sf::Int32>(ServerPacket::CombinaisonRequest);

  if (joueur == Joueur::A)
  {
    if (_socketA.send(packet) != sf::Socket::Done)
      throw std::runtime_error("Erreur de paquet: [CombinaisonRequest] -> "
			       + _nameA);
  }
  else
  {
    if (_socketB.send(packet) != sf::Socket::Done)
      throw std::runtime_error("Erreur de paquet: [CombinaisonRequest] -> "
			       + _nameB);
  }

  // Réception de la combinaison
  packet.clear();

  if (joueur == Joueur::A)
  {
    if (_socketA.receive(packet) != sf::Socket::Done)
      throw std::runtime_error("Erreur de paquet: " + _nameA +
			       " -> [CombinaisonRequest]");
  }
  else
  {
    if (_socketB.receive(packet) != sf::Socket::Done)
      throw std::runtime_error("Erreur de paquet: " + _nameB +
			       " -> [CombinaisonRequest]");
  }
  
  // Extraction de la combinaison
  std::string combiStr;	
  if (!(packet >> combiStr))
    throw std::string("Erreur d'extraction de la combinaison !");

  std::cout << "Combinaison reçu " << combiStr << std::endl;

  Combinaison combinaison;
  combinaison.setPions(combiStr);

  return combinaison;
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
  broadcastMessage("Le gagnant est: " + _game.getGagnantNom());
  
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
void Server::broadcastMessage(const std::string& message)
{
  sf::Packet packet;
  packet << static_cast<sf::Int32>(ServerPacket::BroadcastMessage);
  packet << message;
  
  if (_socketA.send(packet) != sf::Socket::Done)
    throw std::runtime_error("Impossible d'envoyer un message au joueur " + _nameA);

  if (_socketB.send(packet) != sf::Socket::Done)
    throw std::runtime_error("Impossible d'envoyer un message au joueur " + _nameB);
}


////////////////////////////////////////////////////////////
void Server::run()
{
  init();
  mainLoop();
}


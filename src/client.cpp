////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "client.hpp"
#include "protocol.hpp"
#include "Combinaison.hpp"
#include <iostream>
#include <memory>
#include <string>


////////////////////////////////////////////////////////////
Client::Client(GameContext* context) :
  _pSocket(nullptr),
  _context(context),
  _thread(&Client::run, this),
  _endOfGame(false)
{ 
}


////////////////////////////////////////////////////////////
Client::~Client()
{
  
}

////////////////////////////////////////////////////////////
void Client::priv_initClient()
{
  // Connexion au serveur
  _pSocket = std::make_unique<sf::TcpSocket>();
  if (_pSocket->connect(_serverIP, _port) != sf::Socket::Done)
    throw std::string("Impossible de se connecter au serveur: " + _serverIP);

  std::cout << "Connexion au serveur réussie." << std::endl;
 
  // Envoi du pseudo client
  sf::Packet packet;
  packet << _nameClient;
  
  if (_pSocket->send(packet) != sf::Socket::Done)
    throw std::string("Impossible d'envoyer le pseudo client");

  std::cout << "En attente de la confirmation de la combinaison..."
	    << std::endl;
}


////////////////////////////////////////////////////////////
void Client::priv_handlePacket(sf::Int32 packetType, sf::Packet& packet)
{
  switch (packetType)
  {
    
  case PacketType::Confirmation:
  {
    //std::cout << _nameHost << " a choisi la combinaison secrète !" << std::endl;
  } break;

  case PacketType::CombinaisonRequest:
  {
    Combinaison combinaison = Combinaison::fromInput();
    sf::Packet pkt;
    pkt << combinaison;

    if (_pSocket->send(pkt) != sf::Socket::Done)
      throw std::string("Impossible d'envoyer la combinaison !");
  } break;

  case PacketType::TurnFinished:
  {
    sf::Int32 score;
    std::string plateau;

    if (!(packet >> score))
      throw std::string("Paquet corrompu [score] - PacketType::TurnFinished");

    if (!(packet >> plateau))
      throw std::string("Paquet corrompu [plateau] - PacketType::TurnFinished");

    std::cout << "Score du décodeur: " << score << "pts" << std::endl
	      << plateau << std::endl;
    std::cout << "Inversion des rôles !" << std::endl;
  } break;

  case PacketType::TurnNotFinished:
  {
    std::string plateau;

    if (!(packet >> plateau))
      throw std::string("Paquet corrompu - PacketType::TurnNotFinished");

    std::cout << plateau << std::endl;
  } break;
  
  case PacketType::GameFinished:
  {
    std::string gagnant;

    if (!(packet >> gagnant))
      throw std::string("Paquet corrompu - PacketType::GameFinished");

    std::cout << "Le gagnant est " << gagnant << " !" << std::endl
	      << "La partie est terminée !" << std::endl;
    _endOfGame = true;
  } break;
  
  };
}

////////////////////////////////////////////////////////////
void Client::priv_mainLoop()
{
  sf::Packet packet;
  sf::Int32 packetType;
  
  while (!_endOfGame)
  {
    packet.clear();
    if (_pSocket->receive(packet) != sf::Socket::Done)
      throw std::string("Impossible de recevoir des paquets du serveur !");

    if (!(packet >> packetType))
      throw std::string("Impossible d'extraire le type du paquet !");

    priv_handlePacket(packetType, packet);
  }
}

////////////////////////////////////////////////////////////
void Client::run()
{
  while (true)
    std::cout << "Test test stest" << std::endl;
}

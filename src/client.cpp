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
Client::Client() :
  _pSocket(nullptr),
  _endOfGame(false)
{ 
}


////////////////////////////////////////////////////////////
Client::~Client()
{
}


////////////////////////////////////////////////////////////
void Client::priv_getSettings()
{
  
  // Saisie de l'IP du serveur
  do
  {
    std::cout << "Adresse IP du serveur: ";
    std::getline(std::cin, _serverIP);

    if (_serverIP.empty())
      std::cerr << "L'adresse du serveur ne peut être vide !" << std::endl;
  }
  while (_serverIP.empty());

  // Saisie du port
  std::string input;
  
  do
  {
    std::cout << "Port du serveur: ";
    std::getline(std::cin, input);

    try
    {
      _port = std::stoi(input);
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
      std::cerr << "Le port du serveur ne peut être vide !" << std::endl;
    else
    {
      if (_port <= 0)
	std::cerr << "Le port doit être supérieur à 0 !" << std::endl;
    }
  }
  while (input.empty() || _port <= 0);
  
  // Saisie du nom
  do
  {
    std::cout << "Pseudo: ";
    std::getline(std::cin, _nameClient);

    if (_nameClient.empty())
      std::cerr << "Votre pseudo ne peut être vide !" << std::endl;
  }
  while (_nameClient.empty());
}


////////////////////////////////////////////////////////////
void Client::priv_initClient()
{
  // Connexion au serveur
  _pSocket = std::make_unique<sf::TcpSocket>();
  if (_pSocket->connect(_serverIP, _port) != sf::Socket::Done)
    throw std::string("Impossible de se connecter au serveur: " + _serverIP);

  std::cout << "Connexion au serveur réussie." << std::endl;
  
  // Réception du pseudo de l'hôte
  sf::Packet packet;

  if (_pSocket->receive(packet) != sf::Socket::Done)
    throw std::string("Impossible de recevoir le pseudo de l'hôte");

  if (!(packet >> _nameHost))
    throw std::string("Erreur de paquet - réception du pseudo de l'hôte");

  std::cout << "Vous jouer contre " << _nameHost << " !" << std::endl;

  // Envoi du pseudo client
  packet.clear();
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
    std::cout << _nameHost << " a choisi la combinaison secrète !" << std::endl;
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
    std::cout << "La partie est terminée !" << std::endl;
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
  priv_getSettings();
  priv_initClient();
  priv_mainLoop();
}


////////////////////////////////////////////////////////////
int main()
{
  Client client;

  try
  {
    client.run();
  }
  catch (const std::string& error)
  {
    std::cerr << error << std::endl;
  }
  
  return 0;
}

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
  _pSocket(nullptr)
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
}


////////////////////////////////////////////////////////////
void Client::run()
{
  priv_getSettings();
  priv_initClient();
  
  sf::Packet packet;

  if (_pSocket->receive(packet) != sf::Socket::Done)
  {
    throw std::string("Impossible de recevoir le paquet de confirmation");
  }

  std::string plateau;

  if (packet >> _nameHost >> plateau)
  {
    std::cout << _nameHost << " a choisit le code secret !" << std::endl;
  }

  // Première affichage
  std::cout << plateau;

  Combinaison combi = Combinaison::fromInput();

  packet.clear();
  packet << combi;

  // Envoi de la combinaison
  if (_pSocket->send(packet) != sf::Socket::Done)
  {
    throw std::string("Impossible d'envoyer le paquet !");
  }

  // Réception du plateau modifié
  packet.clear();
  if (_pSocket->receive(packet) != sf::Socket::Done)
  {
    throw std::string("Impossible d'envoyer le paquet !");
  }
  
  // Affichage du paquet modifié
  if (packet >> plateau)
    std::cout << plateau;
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

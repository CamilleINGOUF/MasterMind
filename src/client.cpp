////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "client.hpp"
#include <iostream>
#include <string>
#include <memory>
#include "Combinaison.hpp"


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
void Client::run()
{
  std::string ip;
  int port(-1);
  priv_getSettings(ip, port);
  
  // Connexion au serveur
  _pSocket = std::make_unique<sf::TcpSocket>();
  if (_pSocket->connect(ip, port) != sf::Socket::Done)
  {
    throw std::string("Impossible de se connecter au serveur: " + ip); 
  }

  // Attente de la confirmation de la combinaison
  std::cout << "Connexion au serveur réussie." << std::endl;
  std::cout << "En attente de la combinaison..." << std::endl;

  sf::Packet packet;

  if (_pSocket->receive(packet) != sf::Socket::Done)
  {
    throw std::string("Impossible de recevoir le paquet de confirmation");
  }

  std::string plateau;

  if (packet >> _nameHost >> plateau)
  {
    std::cout << "Confirmation reçu de " << _nameHost << std::endl;
    std::cout << plateau.size() << std::endl;
  }

  // Première affichage
  std::cout << plateau;

  // TODO: Check validité de la combinaison
  // Saisie de la combinaison
  std::string input;
  Combinaison combi;

  std::cout << "Saisir une combinaison: ";
  std::cin >> input;

  combi.setPions(input);

  packet.clear();
  packet << combi.toString();

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
void Client::priv_getSettings(std::string& ip, int& port)
{
  
  // Saisie de l'IP du serveur
  do
  {
    std::cout << "Adresse IP du serveur: ";
    std::getline(std::cin, ip);
  }
  while (ip.empty());

  // Saisie du port
  std::string input;
  
  do
  {
    std::cout << "Port du serveur: ";
    std::getline(std::cin, input);

    try
    {
      port = std::stoi(input);
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
  while (input.empty() || port <= 0);
  
  // Saisie du nom
  do
  {
    std::cout << "Pseudo: ";
    std::getline(std::cin, _nameClient);
  }
  while (_nameClient.empty());
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

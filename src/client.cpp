////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "client.hpp"
#include <iostream>
#include <string>
#include <memory>


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

  packet >>_nameHost;
  std::cout << _nameHost << " a choisit sa combinaison" << std::endl;

  // Saisie de la combinaison
  // Tant que la partie n'est pas finie
  while (true)
  {
    std::cout << "Saisie de la combinaison: " << std::endl;

    // Envoi du paquet
    packet.clear();
    // Réponse du serveur
    _pSocket->send(packet);
    // Continuer la partie ?
    
  }
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

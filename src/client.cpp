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
  // TODO: Check des inputs
  // Saisie de l'IP du serveur
  std::string ip;
  std::cout << "Adresse IP du serveur: ";
  std::cin >> ip;

  // Saisie du port
  unsigned port;
  std::cout << "Port du serveur: ";
  std::cin >> port;

  // Saisie du nom
  std::string name;
  std::cout << "Pseudo: ";
  std::cin >> _nameClient;

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
}


////////////////////////////////////////////////////////////
int main(int argc, char** argv)
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

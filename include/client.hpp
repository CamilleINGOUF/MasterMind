////////////////////////////////////////////////////////////
//
// Mastermind
// Copyright (C) 2017 - CAFA
//
////////////////////////////////////////////////////////////


#ifndef CLIENT_HPP_
#define CLIENT_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <SFML/Network.hpp>
#include <memory>
#include <string>

typedef std::unique_ptr<sf::TcpSocket> PtrSocket;


////////////////////////////////////////////////////////////
/// \brief Représente un joueur
///
////////////////////////////////////////////////////////////
class Client
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Constructeur d'un client
  ///
  ////////////////////////////////////////////////////////////
  Client();

  ////////////////////////////////////////////////////////////
  /// \brief Destructeur du client
  ///
  ////////////////////////////////////////////////////////////
  ~Client();

  ////////////////////////////////////////////////////////////
  /// \brief Lancement du client
  ///
  ////////////////////////////////////////////////////////////
  void run();
  
private:

  ////////////////////////////////////////////////////////////
  /// \brief Récupère les données pour rejoindre une partie
  ///
  /// \param ip l'adresse ip du serveur
  /// \param port le port du serveur
  ///
  ////////////////////////////////////////////////////////////
  void priv_getSettings(std::string& ip, int& port);

  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  PtrSocket _pSocket;      ///< Lien entre le serveur et le client
  std::string _nameClient; ///< Le pseudo du client
  std::string _nameHost;   ///< Le pseudo de l'hôte
  
};

#endif // CLIENT_HPP_

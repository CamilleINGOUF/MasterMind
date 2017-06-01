////////////////////////////////////////////////////////////
//
// Mastermind
// Copyright (C) 2017 - CAFA
//
////////////////////////////////////////////////////////////


#ifndef SERVER_HPP_
#define SERVER_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <SFML/Network.hpp>
#include <memory>
#include <string>

typedef std::unique_ptr<sf::TcpSocket> PtrSocket;
typedef std::unique_ptr<sf::TcpListener> PtrListener;


////////////////////////////////////////////////////////////
/// \brief Hébergeur d'une partie
///
////////////////////////////////////////////////////////////
class Server
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Constructeur du serveur
  ///
  /// \param port le port du serveur
  ///
  ////////////////////////////////////////////////////////////
  Server(unsigned port);

  ////////////////////////////////////////////////////////////
  /// \brief Le destructeur du serveur
  ///
  ////////////////////////////////////////////////////////////
  ~Server();

  ////////////////////////////////////////////////////////////
  /// \brief Démarre le serveur
  ///
  ////////////////////////////////////////////////////////////
  void run();
  
private:

  ////////////////////////////////////////////////////////////
  /// \brief Recupère les paramètres du serveur depuis l'entrée
  /// standard
  ///
  ////////////////////////////////////////////////////////////
  void priv_getSettings();
  
  ////////////////////////////////////////////////////////////
  /// \brief Initialise le serveur
  ///
  ////////////////////////////////////////////////////////////
  void priv_initServer();
  
  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  unsigned    _port;       ///< Le port du serveur
  PtrSocket   _pSocket;    ///< La socket qui fait le lien entre les 2 machines
  PtrListener _pListener;  ///< Le listener pour attendre la connexion du client
  std::string _nameHost;   ///< Le pseudo de l'hôte
  std::string _nameClient; ///< Le pseudo du client
  int         _nbManches;  ///< Le nombre total de manches
};

#endif // SERVER_HPP_

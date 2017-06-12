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
#include "GameContext.hpp"

#include <memory>
#include <string>
#include <SFML/Network.hpp>
#include <SFML/System/Thread.hpp>


typedef std::unique_ptr<sf::TcpSocket> PtrSocket;


////////////////////////////////////////////////////////////
/// \brief Partie client du mastermind
///
////////////////////////////////////////////////////////////
class Client
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Constructeur d'un client
  ///
  ////////////////////////////////////////////////////////////
  Client(GameContext* context);

  ////////////////////////////////////////////////////////////
  /// \brief Destructeur du client
  ///
  ////////////////////////////////////////////////////////////
  ~Client();

  ////////////////////////////////////////////////////////////
  /// \brief Fonction associée au thread
  ///
  ////////////////////////////////////////////////////////////
  void run();

  ////////////////////////////////////////////////////////////
  /// \brief Fonction qui démarre le thread
  ///
  ////////////////////////////////////////////////////////////
  void start();

  ////////////////////////////////////////////////////////////
  /// \brief Retourne True si le client est connecté au serveur
  ///
  ////////////////////////////////////////////////////////////
  bool isConnected();

  ////////////////////////////////////////////////////////////
  /// \brief Envoie un message de déconnexion
  ///
  ////////////////////////////////////////////////////////////
  void disconnected();
  
private:

  ////////////////////////////////////////////////////////////
  /// \brief Phase d'initialisation du jeu entre le client et le
  /// serveur
  ///
  ////////////////////////////////////////////////////////////
  void priv_initClient();

  ////////////////////////////////////////////////////////////
  /// \brief Boucle principale du client
  ///
  ////////////////////////////////////////////////////////////
  void priv_mainLoop();

  ////////////////////////////////////////////////////////////
  /// \brief Gestion des paquets
  ///
  /// \param packetType le type du paquet (cf. protocol.hpp)
  /// \param packet les données
  ///
  //////////////////////////////////////////////////////////// 
  void priv_handlePacket(sf::Int32 packetType, sf::Packet& packet);
  
  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  PtrSocket   _pSocket;      ///< Lien entre le serveur et le client
  std::string _nameClient;   ///< Le pseudo du client
  std::string _nameOpponent; ///< Le pseudo de l'adversaire
  std::string _serverIP;     ///< L'adresse du serveur
  unsigned    _port;         ///< Le port du serveur
  GameContext* _context;     ///< Le contexte du jeu
  sf::Thread*  _thread;       ///< La gestion réseau non bloquante
  bool        _endOfGame;    ///< Flag de la boucle principale
  bool        _connected;    ///< Flag pour la connectivité
};

#endif // CLIENT_HPP_

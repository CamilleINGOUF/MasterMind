#ifndef SERVER_HPP_
#define SERVER_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "Mastermind.hpp"

#include <memory>
#include <string>
#include <SFML/Network.hpp>

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
  /// \param nbManches le nombre de manches
  ///
  ////////////////////////////////////////////////////////////
  Server(unsigned port, unsigned nbManches);

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
  /// \brief Initialise le serveur
  ///
  ////////////////////////////////////////////////////////////
  void init();

  ////////////////////////////////////////////////////////////
  /// \brief Gestion d'un tour
  ///
  ////////////////////////////////////////////////////////////
  void updateTour();
  
  ////////////////////////////////////////////////////////////
  /// \brief Boucle principale
  ///
  ////////////////////////////////////////////////////////////
  void mainLoop();

  ////////////////////////////////////////////////////////////
  /// \brief Retourne une combinaison reçu d'un client
  ///
  /// \param joueur le destinaire de la requête
  /// \param combiSecrete la combinaison demandée est la combinaison
  /// secrète
  ///
  ////////////////////////////////////////////////////////////
  Combinaison requestCombinaison(Joueur joueur, bool combiSecrete);
  
  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  unsigned        _port;     ///< Le port du serveur
  sf::TcpListener _listener; ///< Accepte les nouvelles connexions
  std::string     _nameA;    ///< Le pseudo du client A
  std::string     _nameB;    ///< Le pseudo du client B
  sf::TcpSocket   _socketA;  ///< La socket du client A
  sf::TcpSocket   _socketB;  ///< La socket du client B
  Mastermind      _game;     ///< L'instance de jeu
};


#endif // SERVER_HPP_

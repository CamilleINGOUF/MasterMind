#ifndef NETWORK_STATE_HPP_
#define NETWORK_STATE_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "Button.hpp"
#include "GameState.hpp"
#include "Board.hpp"
#include "IconButton.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/System/Time.hpp>

////////////////////////////////////////////////////////////
/// \brief Etat en jeu
////////////////////////////////////////////////////////////
class NetworkState : public GameState
{
public:
  NetworkState(GameContext* context);
  virtual ~NetworkState() override;
  virtual void init() override;
  virtual void update(sf::Time dt) override;
  virtual void handleEvent(sf::Event& event) override;
  virtual void draw() override;

  //////////////////////////////////////////////////////////
  /// \brief Met en place la connexion
  ///
  //////////////////////////////////////////////////////////
  void prepare();
  
private:
  //////////////////////////////////////////////////////////
  /// \brief On passe au menu principal
  ///
  //////////////////////////////////////////////////////////
  void switchToMenuState();

  ////////////////////////////////////////////////////////////
  /// \brief Gestion des différents paquets reçu par le serveur
  ///
  /// \param packetType le type du paquet
  /// \param packet les données
  ///
  ////////////////////////////////////////////////////////////
  void handlePacket(sf::Int32 packetType, sf::Packet& packet);

  ////////////////////////////////////////////////////////////
  /// \brief Mise à jour graphique des scores
  ///
  ////////////////////////////////////////////////////////////
  void refreshScores();

  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  Button        _backToMenu;     ///< Bouton retour au menu
  sf::TcpSocket _socket;         ///< Le lien entre le client et le serveur
  sf::Time      _timeoutTimer;   ///< Timer pour le timeout
  sf::Time      _retryTimer;     ///< Timer pour le retry
  int           _retryCount;     ///< Le nombre de reconnexions
  bool          _connected;      ///< Indique si on est connecté au serveur
  bool          _sendingAllowed; ///< Autorise l'envoi de la combinaison
  sf::Text      _statusText;     ///< Texte sur le status du jeu
  Button        _validateButton; ///< Le bouton valider
  Board         _board;          ///< Le plateau de jeu
  std::string   _clientName;     ///< Le pseudo du joueur courant
  std::string   _opponentName;   ///< Le pseudo de l'adversaire
  sf::Text      _clientText;     ///< Les infos du joueur courant
  sf::Text      _opponentText;   ///< Les infos du de l'adversaire
  sf::Int32     _clientScore;    ///< Le score du joueur courant
  sf::Int32     _opponentScore;  ///< Le score de l'adversaire
  bool          _gameFinished;
  sf::Time      _gameFinishedTimer;
  IconButton    _speakerButton;
};


#endif // NETWORK_STATE_HPP_

#ifndef NETWORK_STATE_HPP_
#define NETWORK_STATE_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "Button.hpp"
#include "GameState.hpp"
#include "PionDrawable.hpp"

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
  virtual void update(sf::Time dt) override;
  virtual void handleEvent(sf::Event& event) override;
  virtual void draw() override;

  //////////////////////////////////////////////////////////
  /// \brief Met en place les connexions
  ///
  //////////////////////////////////////////////////////////
  void prepare();
  
private:
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
  /// Données membres
  ////////////////////////////////////////////////////////////
  Button        _backToMenu;   ///< Bouton retour au menu
  sf::TcpSocket _socket;       ///< Le lien entre le client et le serveur
  sf::Time      _timeoutTimer; ///< Timer pour le timeout 
  bool          _connected;    ///< Indique si on est connecté au serveur
  sf::Text      _statusText;   ///< Texte sur le status du jeu
};


#endif // NETWORK_STATE_HPP_

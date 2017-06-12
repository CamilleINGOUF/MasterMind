#ifndef NETWORK_STATE_HPP_
#define NETWORK_STATE_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "Button.hpp"
#include "GameState.hpp"

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

  Button _backToMenu;      //< Bouton retour au menu

  // Partie graphique
  sf::Font _font;        ///< Police du texte
  
  // Partie réseau
  sf::TcpSocket _socket; ///< Le lien entre le client et le serveur
  sf::Time      _timeoutTimer;
};


#endif // NETWORK_STATE_HPP_

#ifndef NETWORK_STATE_HPP_
#define NETWORK_STATE_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "GameState.hpp"
#include "Button.hpp"

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
  void handlePacket(sf::Int32 packetType, sf::Packet& packet);
  
  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////

  // Partie graphique
  sf::Text _waitingText; ///< Texte affiché pendant le jeu
  sf::Font _font;        ///< Police du texte
  Button   _backToMenu;  ///< Bouton retour au menu

  // Partie réseau
  sf::TcpSocket _socket; ///< Le lien entre le client et le serveur
  sf::Time      _timeoutTimer;
};


#endif // NETWORK_STATE_HPP_

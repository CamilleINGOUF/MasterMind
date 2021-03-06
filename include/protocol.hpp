#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "Combinaison.hpp"
#include "Plateau.hpp"
#include <SFML/Network.hpp>


////////////////////////////////////////////////////////////
/// \brief Identifiants pour des paquets
////////////////////////////////////////////////////////////
namespace ServerPacket
{
  enum ID
  {
    NameRequest,
    BroadcastMessage,
    GameBegin,
    CombinaisonRequest,
    TurnNotFinished,
    TurnFinished,
    GameFinished,
    PlayerDisconnected
  };
}

////////////////////////////////////////////////////////////
sf::Packet& operator<<(sf::Packet& pkt, const Combinaison& combi)
{
  return pkt << combi.toString();
}


////////////////////////////////////////////////////////////
sf::Packet& operator<<(sf::Packet& pkt, const Plateau& p)
{
  return pkt << p.toString();
}


#endif // PROTOCOL_HPP_

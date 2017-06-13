#ifndef JOINING_STATE_HPP_
#define JOINING_STATE_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "Button.hpp"
#include "GameState.hpp"
#include "TextField.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>


////////////////////////////////////////////////////////////
/// \brief Le menu principal
////////////////////////////////////////////////////////////
class JoiningState : public GameState
{
public:
  JoiningState(GameContext* context);
  virtual ~JoiningState() override;
  virtual void update(sf::Time dt) override;
  virtual void handleEvent(sf::Event& event) override;
  virtual void draw() override;
  
private:
  bool validInput();
  
  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  Button _cancel;
  Button _joinGame;

  TextField _hostAddress;
  TextField _nickname;
};


#endif // JOINING_STATE_HPP_

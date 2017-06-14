#ifndef ASSETS_DECLARATIONS_HPP_
#define ASSETS_DECLARATIONS_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>


namespace Textures
{
  enum ID
  {
    Coin,
    Board,
    CoinHolder
  };
}

namespace Sounds
{
  enum ID
  {
    Coin
  };
}

namespace Musics
{
  enum ID
  {
    Menu,
    InGame
  };
}

namespace Fonts
{
  enum ID
  {
    Arial
  };
}

template<typename Resource, typename Identifier>
class AssetManager;

typedef AssetManager<sf::Texture, Textures::ID> TextureManager;
typedef AssetManager<sf::Font, Fonts::ID> FontManager;

// TODO: Sound ? Music ?

#endif // AssetsDeclarations

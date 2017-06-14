////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "MusicPlayer.hpp"

#include <stdexcept>
#include <SFML/Audio/SoundSource.hpp>

////////////////////////////////////////////////////////////
MusicPlayer::MusicPlayer()
{
  _playlist[Musics::Menu]   = "../media/musics/awesomeness.wav";
  _playlist[Musics::InGame] = "../media/musics/drumbeat.ogg";
}


////////////////////////////////////////////////////////////
void MusicPlayer::play(Musics::ID id)
{
  if (!_music.openFromFile(_playlist[id]))
    throw std::runtime_error("Impossible d'ouvrir la musique " + _playlist[id]);

  _music.setVolume(100.f);
  _music.setLoop(true);
  _music.play();
}


////////////////////////////////////////////////////////////
void MusicPlayer::mute()
{
  if (_music.getStatus() != sf::SoundSource::Playing)
    return;

  _music.setVolume(0.f);
}


////////////////////////////////////////////////////////////
void MusicPlayer::unmute()
{
  if (_music.getStatus() != sf::SoundSource::Playing)
    return;

  _music.setVolume(100.f);
}

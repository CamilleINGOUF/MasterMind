/////////////////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////////////////
#include "mastermind.hpp"

////////////////////////////////////////////////////////////
Mastermind::Mastermind(): _codeur(Serveur), _decodeur(Client)
			, _tourDansManche(0), _isRunning(false)
			{}
			  
int Mastermind::getNbManches() const
{
  return _nbManches;
}

void Mastermind::setNbManches(const int v)
{
  _nbManches = v;
  _currentNbManches = v;
}

int Mastermind::getCurrentNbManches() const
{
  return _currentNbManches;
}

void Mastermind::setCurrentNbManches(const int v)
{
  _currentNbManches = v;
}

Plateau Mastermind::getPlateau() const
{
  return _plateau;
}

void Mastermind::setPlateau(const Plateau plateau)
{
  _plateau = plateau;
}

std::string Mastermind::getNomJoueurServeur() const
{
  return _nomJoueurServeur;
}

std::string Mastermind::getNomJoueurClient() const
{
  return _nomJoueurClient;
}

void Mastermind::setNomJoueurServeur(const std::string nom)
{
  _nomJoueurServeur = nom;
}

void Mastermind::setNomJoueurClient(const std::string nom)
{
  _nomJoueurClient = nom;
}

std::string Mastermind::getGagnantNom() const
{
  return _gagnantNom;
}

int Mastermind::getScoreServeur() const
{
  return _scoreServeur;
}

void Mastermind::setScoreServeur(const int v)
{
  _scoreServeur = v;
}

int Mastermind::getScoreClient() const
{
  return _scoreClient;
}

void Mastermind::setScoreClient(const int v)
{
  _scoreClient = v;
}

void Mastermind::setGagnantNom(const std::string nom)
{
  _gagnantNom = nom;
}

const Combinaison Mastermind::getCodeSecret()
{
  return _codeSecret;
}

void Mastermind::setCodeSecret(const Combinaison combinaison)
{
  _codeSecret = combinaison;
}

void Mastermind::inverserRoles()
{
  if(_codeur == Serveur)
    {
      _decodeur = Serveur;
      _codeur = Client;
    }
  else
    {
      _decodeur = Client;
      _codeur = Serveur;
    }
  
  if(_tourDansManche == 1)
    nouvelleManche();
  else
    _tourDansManche++;
  viderPlateau();
}
  
void Mastermind::nouvelleManche()
{
      _tourDansManche = 0;
      _currentNbManches--;
}

void Mastermind::ajoutPoints(Joueur joueur, int v)
{
  if(joueur == Client)
    _scoreClient += v;
  else
    _scoreServeur += v;
}

bool Mastermind::partieTerminee()
{
  return _currentNbManches <= 0;
}

bool Mastermind::mancheTerminee()
{
  return _tourDansManche == 1;
}

bool Mastermind::tourTermine()
{
  return _plateau.getCombinaisons().size() >= 12
    or decodeurGagnant();
}

bool Mastermind::decodeurGagnant()
{
  if(_codeSecret == _plateau.getLastCombinaison())
    {
      if(_decodeur == Serveur)
	{
	  _gagnantNom = _nomJoueurServeur;
	  _gagnantJoueur = Serveur;
	}
      else
	{
	  _gagnantNom = _nomJoueurClient;
	  _gagnantJoueur = Client;
	}
      return true;
    }
  return false;
}

void Mastermind::viderPlateau()
{
  Plateau p;
  setPlateau(p);
}

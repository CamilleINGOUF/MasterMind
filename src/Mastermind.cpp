/////////////////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////////////////
#include "Mastermind.hpp"


////////////////////////////////////////////////////////////
Mastermind::Mastermind() :
  _tourDansManche(0),
  _codeur(Joueur::A),
  _decodeur(Joueur::B),
  _scoreA(0),
  _scoreB(0)
{
}


////////////////////////////////////////////////////////////
int Mastermind::getNbManches() const
{
  return _nbManches;
}


////////////////////////////////////////////////////////////
void Mastermind::setNbManches(const int v)
{
  _nbManches = v;
  _currentNbManches = v;
}


////////////////////////////////////////////////////////////
int Mastermind::getCurrentNbManches() const
{
  return _currentNbManches;
}


////////////////////////////////////////////////////////////
void Mastermind::setCurrentNbManches(const int v)
{
  _currentNbManches = v;
}


////////////////////////////////////////////////////////////
Plateau& Mastermind::getPlateau()
{
  return _plateau;
}


////////////////////////////////////////////////////////////
void Mastermind::setPlateau(const Plateau& plateau)
{
  _plateau = plateau;
}


////////////////////////////////////////////////////////////
const std::string& Mastermind::getNomJoueurA() const
{
  return _nomJoueurA;
}


////////////////////////////////////////////////////////////
const std::string& Mastermind::getNomJoueurB() const
{
  return _nomJoueurB;
}


////////////////////////////////////////////////////////////
void Mastermind::setNomJoueurA(const std::string& nom)
{
  _nomJoueurA = nom;
}


////////////////////////////////////////////////////////////
void Mastermind::setNomJoueurB(const std::string& nom)
{
  _nomJoueurB = nom;
}


////////////////////////////////////////////////////////////
const std::string Mastermind::getGagnantNom()
{
  if(_scoreA > _scoreB)
    {
      _gagnantJoueur = Joueur::A;
      return _nomJoueurA;
    }
  else if(_scoreA < _scoreB)
    {
      _gagnantJoueur = Joueur::B;
      return _nomJoueurB;
    }
  return _nomJoueurB + " et " + _nomJoueurA; 
  
}


////////////////////////////////////////////////////////////
int Mastermind::getScoreJoueurA() const
{
  return _scoreA;
}


////////////////////////////////////////////////////////////
void Mastermind::setScoreJoueurA(const int v)
{
  _scoreA = v;
}


////////////////////////////////////////////////////////////
int Mastermind::getScoreJoueurB() const
{
  return _scoreB;
}


////////////////////////////////////////////////////////////
void Mastermind::setScoreJoueurB(const int v)
{
  _scoreB = v;
}


////////////////////////////////////////////////////////////
void Mastermind::setGagnantNom(const std::string& nom)
{
  _gagnantNom = nom;
}


////////////////////////////////////////////////////////////
const Combinaison& Mastermind::getCodeSecret()
{
  return _codeSecret;
}


////////////////////////////////////////////////////////////
void Mastermind::setCodeSecret(const Combinaison& combinaison)
{
  _codeSecret = combinaison;
}


////////////////////////////////////////////////////////////
void Mastermind::inverserRoles()
{
  if (_codeur == Joueur::A)
  {
    _decodeur = Joueur::A;
    _codeur   = Joueur::B;
  }
  else
  {
    _decodeur = Joueur::B;
    _codeur   = Joueur::A;
  }
  
  if (_tourDansManche == 1)
    nouvelleManche();
  else
    _tourDansManche++;
  
  viderPlateau();
}


////////////////////////////////////////////////////////////
void Mastermind::nouvelleManche()
{
  _tourDansManche = 0;
  _currentNbManches--;
}


////////////////////////////////////////////////////////////
void Mastermind::ajoutPoints(Joueur joueur, int v)
{
  if (joueur == Joueur::A)
    _scoreA += v;
  else
    _scoreB += v;
}


////////////////////////////////////////////////////////////
bool Mastermind::partieTerminee()
{
  return _currentNbManches <= 0;
}


////////////////////////////////////////////////////////////
bool Mastermind::mancheTerminee()
{
  return partieTerminee() or (_tourDansManche == 1 and tourTermine());
}


////////////////////////////////////////////////////////////
bool Mastermind::tourTermine()
{
  return partieTerminee() or (_plateau.getCombinaisons().size() >= 12
	  or decodeurGagnant());
}


////////////////////////////////////////////////////////////
bool Mastermind::decodeurGagnant()
{
  if (getNombreEssais() == 0)
    return false;
  
  if (_codeSecret == _plateau.getLastCombinaison())
  {
    return true;
  }

  return false;
}


////////////////////////////////////////////////////////////
void Mastermind::viderPlateau()
{
  _plateau.getCombinaisons().clear();
  _plateau.getCorrections().clear();
}


////////////////////////////////////////////////////////////
bool Mastermind::plateauVide()
{
  return _plateau.getNbCombinaisons() == 0;
}


////////////////////////////////////////////////////////////
Joueur Mastermind::getDecodeur() const
{
  if (_decodeur == Joueur::A)
    return Joueur::A;

  return Joueur::B;
}


////////////////////////////////////////////////////////////
void Mastermind::ajouterCombinaison(Combinaison& combi)
{
  _plateau.addCombinaison(combi);
}


////////////////////////////////////////////////////////////
unsigned Mastermind::getNombreEssais() const
{
  return _plateau.getNbCombinaisons();
}


////////////////////////////////////////////////////////////
void Mastermind::corrigerDerniereCombinaison()
{
  Combinaison correction;
  std::vector<Pion> pions;

 
  for (int i = 0; i < 4;i++)
  {
    if (_codeSecret.getPions()[i] == _plateau.getLastCombinaison().getPions()[i])
    {
      pions.push_back(blanc);
    }
    else if(_codeSecret.pionDansLaCombinaison(_plateau
					      .getLastCombinaison()
					      .getPions()[i]))
    {
      pions.push_back(noir);
    }
    else
    {
      pions.push_back(vide);
    }
  }

  correction.setPions(pions);
  _plateau.addCorrection(correction);
}


////////////////////////////////////////////////////////////
Joueur Mastermind::getGagnant() const
{
  if (_gagnantJoueur == Joueur::A)
    return Joueur::A;

  return Joueur::B;
}

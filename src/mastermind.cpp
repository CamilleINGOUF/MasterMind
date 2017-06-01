/////////////////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////////////////
#include "mastermind.hpp"

////////////////////////////////////////////////////////////
Mastermind::Mastermind(){}

int Mastermind::getNbManches() const
{
  return _nbManches;
}

void Mastermind::setNbManches(const int v)
{
  _nbManches = v;
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

std::string Mastermind::getGagnant() const
{
  return _gagnant;
}

void Mastermind::setGagnant(const std::string nom)
{
  _gagnant = nom;
}

Combinaison Mastermind::getCodeSecret() const
{
  return _codeSecret;
}

void Mastermind::setCodeSecret(const Combinaison combinaison)
{
  _codeSecret = combinaison;
}


/////////////////////////////////////////////////////////////
void Mastermind::run()
{
  
}

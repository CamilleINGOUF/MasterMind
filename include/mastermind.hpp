#ifndef MASTERMIND_HPP
#define MASTERMIND_HPP

#include "Plateau.hpp"
#include <string>

enum Joueur
  {
    Client,
    Serveur
  };

//////////////////////////////////////////////////////////////////
/// \brief La classe MasterMind est la classe principale du jeu.
/// \file      mastermind.hpp
/// \author    Axel segard
/// \version   1.2
/// \date 31 mai 2017
/////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief La classe du jeu de base
////////////////////////////////////////////////////////////
class Mastermind
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Constructeur par défaut
  ////////////////////////////////////////////////////////////
  Mastermind();

  int getNbManches() const;
  void setNbManches(const int v);

  Plateau getPlateau() const;
  void setPlateau(const Plateau plateau);

  std::string getNomJoueurServeur() const;
  std::string getNomJoueurClient() const;
  void setNomJoueurServeur(const std::string nom);
  void setNomJoueurClient(const std::string nom);

  std::string getGagnant() const;
  void setGagnant(const std::string nom);

  Combinaison getCodeSecret() const;
  void setCodeSecret(const Combinaison combinaison);

  ////////////////////////////////////////////////////////////
  /// \brief Lance le jeu
  ////////////////////////////////////////////////////////////
  void run();

  void inverserRoles();
  
  void nouvelleManche();

  void ajoutPoints();

  bool gameIsOver();
private:
  int _nbManches;
  Plateau _plateau;

  Combinaison _codeSecret;

  std::string _nomJoueurServeur;
  std::string _nomJoueurClient;

  Joueur _codeur;
  Joueur _decodeur;

  std::string _gagnant;
};

#endif

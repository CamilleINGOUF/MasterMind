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
/// \author    Camille Ingouf
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

  Plateau& getPlateau();
  int getCurrentNbManches() const;
  void setCurrentNbManches(const int v);

  void setPlateau(const Plateau plateau);

  std::string getNomJoueurServeur() const;
  std::string getNomJoueurClient() const;
  void setNomJoueurServeur(const std::string nom);
  void setNomJoueurClient(const std::string nom);

  std::string getGagnantNom() const;
  void setGagnantNom(const std::string nom);

  int getScoreServeur() const;
  void setScoreServeur(const int v);
  int getScoreClient() const;
  void setScoreClient(const int v);

  bool decodeurGagnant();

  const Combinaison getCodeSecret();
  void setCodeSecret(const Combinaison combinaison);
  bool plateauVide();

  Joueur getDecodeur() const;

  ////////////////////////////////////////////////////////////
  /// \brief Lance le jeu
  ////////////////////////////////////////////////////////////
  void run();

  void inverserRoles();
  
  void nouvelleManche();

  void viderPlateau();

  void ajoutPoints(Joueur joueur, int v);

  bool partieTerminee();

  bool mancheTerminee();

  bool tourTermine();

  void ajouterCombinaison(Combinaison& combi);

  unsigned getNombreEssais() const;
private:
  int _nbManches;
  int _currentNbManches;

  int _tourDansManche;// tour 1, puir tour 2
  
  Plateau _plateau;

  Combinaison _codeSecret;

  std::string _nomJoueurServeur;
  std::string _nomJoueurClient;

  Joueur _codeur;
  Joueur _decodeur;

  int _scoreServeur;
  int _scoreClient;

  bool _isRunning;

  std::string _gagnantNom;
  Joueur _gagnantJoueur;
};

#endif

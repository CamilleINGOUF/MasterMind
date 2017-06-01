#ifndef MASTERMIND_HPP
#define MASTERMIND_HPP

#include "Plateau.hpp"
#include <string>

enum Joueur
  {
    Client,
    Serveur
  };

////////////////////////////////////////////////////////////
/// \brief La classe du jeu de base
////////////////////////////////////////////////////////////
class MasterMind
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Constructeur par défaut
  ////////////////////////////////////////////////////////////
  MasterMind();

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
  Plateau plateau;

  Combinaison _codeSecret;

  std::string _nomJoueurServeur;
  std::string _nomJoueurClient;

  Joueur _codeur;
  Joueur _decodeur;

  std::string _gagnant;
};

#endif

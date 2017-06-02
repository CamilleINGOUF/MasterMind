////////////////////////////////////////////////////////////
//
// Mastermind
// Copyright (C) 2017 - CAFA
//
////////////////////////////////////////////////////////////


#ifndef COMBINAISON_HPP_
#define COMBINAISON_HPP_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Pion.hpp"
#include <vector>
#include <string>


////////////////////////////////////////////////////////////
/// \brief Modélise une combinaison de 4 pions (couleurs)
////////////////////////////////////////////////////////////
class Combinaison
{  
public:
  ////////////////////////////////////////////////////////////
  /// \brief Constructeur par défaut
  ///
  ////////////////////////////////////////////////////////////
  Combinaison();

  //Combinaison(std::string str);
  Combinaison(std::vector<Pion> pions);

  ////////////////////////////////////////////////////////////
  /// \brief Le destructeur de combinaison
  ///
  ////////////////////////////////////////////////////////////
  ~Combinaison();

  ////////////////////////////////////////////////////////////
  /// \brief Retourne les composants de la combinaison
  ///
  /// \return les composants de la combinaison
  ///
  ////////////////////////////////////////////////////////////
  std::vector<Pion> getPions() const;

  ////////////////////////////////////////////////////////////
  /// \brief Définit les composants de la combinaison
  ///
  /// \param pions les pions constituants la combinaison
  ///
  ////////////////////////////////////////////////////////////
  void setPions(const std::vector<Pion> pions);

  void setPions(const std::string pions);
  
  bool operator==(const Combinaison & that) const;
  Combinaison & operator=(const Combinaison & c);

  ////////////////////////////////////////////////////////////
  /// \brief Retourne la combinaison en str
  ///
  ////////////////////////////////////////////////////////////
  const std::string toString() const;
  
  ////////////////////////////////////////////////////////////
  /// \brief Retourne une combinaison précédément tapée
  ///
  ////////////////////////////////////////////////////////////
  static Combinaison fromInput();


  ////////////////////////////////////////////////////////////
  /// \brief Retourne true si le caractère est autorisé pour une combinaison
  ///
  ////////////////////////////////////////////////////////////
  static bool isColor(const char c);
  
private:
  ////////////////////////////////////////////////////////////
  /// \brief Retourne true si il est possible de créer
  /// une combinaison à partir d'une châine de caractères
  ///
  ////////////////////////////////////////////////////////////
  static bool priv_isValid(const std::string& input);

  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  std::vector<Pion> _pions; ///< Les 4 pions
};

std::ostream & operator<<(std::ostream & os, const Combinaison & c);
std::istream & operator>>(std::istream & is,  Combinaison & c);

bool isCombinaisonValid(const std::string& input);

#endif

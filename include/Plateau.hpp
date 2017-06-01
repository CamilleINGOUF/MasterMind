#ifndef PLATEAU_HPP_
#define PLATEAU_HPP_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <vector>
#include "Combinaison.hpp"


////////////////////////////////////////////////////////////
/// \brief Le plateau de jeu
////////////////////////////////////////////////////////////
class Plateau
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Constructeur par défaut
  ///
  ////////////////////////////////////////////////////////////
  Plateau();

  ////////////////////////////////////////////////////////////
  /// \brief Construit le plateau avec les combinaisons
  ///
  /// \param combinaisons les combinaisons
  ///
  ////////////////////////////////////////////////////////////
  Plateau(std::vector<Combinaison>);

  ////////////////////////////////////////////////////////////
  /// \brief Destructeur
  ///
  ////////////////////////////////////////////////////////////
  ~Plateau();

  ////////////////////////////////////////////////////////////
  /// \brief Retourne l'ensemble des combinaisons jouées
  ///
  /// \return les combinaisons jouées
  ///
  ////////////////////////////////////////////////////////////
  std::vector<Combinaison> getCombinaisons() const;

  ////////////////////////////////////////////////////////////
  /// \brief Définit les combinaisons
  ///
  ////////////////////////////////////////////////////////////
  void setCombinaisons(const std::vector<Combinaison> combinaisons);


  ////////////////////////////////////////////////////////////
  /// \brief Retourne la dernière combinaison jouée
  ///
  /// \return la dernière combinaison jouée
  ///
  ////////////////////////////////////////////////////////////
  Combinaison getLastCombinaison() const;

  ////////////////////////////////////////////////////////////
  /// \brief Ajoute une combinaison à l'historique des coups joués
  ///
  /// \param combinaison la combinaison à jouer
  ///
  ////////////////////////////////////////////////////////////
  void addCombinaison(const Combinaison combinaison);
  
private:
  
  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  std::vector<Combinaison> _combinaisons; ///< Historique des coups joués
};


std::ostream & operator<<(std::ostream & os, const Plateau & p);
std::istream & operator>>(std::istream & is,  Plateau & p);

#endif
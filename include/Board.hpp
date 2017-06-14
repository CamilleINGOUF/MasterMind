#ifndef _BOARD_HPP
#define _BOARD_HPP

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "AssetsDeclarations.hpp"
#include "AssetManager.hpp"
#include "correctionDrawable.hpp"
#include "Combinaison.hpp"
#include "PanelPions.hpp"
#include "Button.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
/// \brief Le plateau de jeu sous forme graphique.
/// Celui-ci effectue les conversions entre la partie
/// graphique et les données
////////////////////////////////////////////////////////////
class Board : public sf::Drawable
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Construit le plateau 
  /// 
  /// \param textureManager le gestionnaire de textures
  /// \param fontManager le gestionnaire de polices
  ///
  ////////////////////////////////////////////////////////////
  Board(TextureManager* textureManager, FontManager* fontManager);

  ////////////////////////////////////////////////////////////
  /// \brief Gestion des événements
  /// 
  /// \param event voir sf::Event
  ///
  ////////////////////////////////////////////////////////////
  void catchEvent(sf::Event& event);

  ////////////////////////////////////////////////////////////
  /// \brief Ré-initialise l'état du plateau (pions choisis)
  ///
  ////////////////////////////////////////////////////////////
  void reset();

  ////////////////////////////////////////////////////////////
  /// \brief Valide la combinaison sélectionnée
  ///
  ////////////////////////////////////////////////////////////
  bool validateCombi();

  ////////////////////////////////////////////////////////////
  /// \brief Retourne la combinaison validée en chaîne de
  /// caractères et reset la sélection de pions
  ///
  /// \return la combinaison validée
  ///
  ////////////////////////////////////////////////////////////
  const std::string getValidatedCombi();

  ////////////////////////////////////////////////////////////
  /// \brief Convertit la plateau au format graphique
  ///
  /// \param board le plateau sous forme de chaîne de caractères
  ///
  /// \return True si le plateau est valide, false sinon
  ///
  ////////////////////////////////////////////////////////////
  bool doBoard(std::string board);

  ////////////////////////////////////////////////////////////
  /// \brief Vérifie que le caractère est autorisé pour créer une combinaison
  ///
  /// \return True si le caractère est valide, false sinon
  ///
  ////////////////////////////////////////////////////////////
  bool isValid(char ch);

  ////////////////////////////////////////////////////////////
  /// \brief Vide le plateau des pions dessinables
  ///
  ////////////////////////////////////////////////////////////
  void empty();
  
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  ////////////////////////////////////////////////////////////
  /// Données membres
  ////////////////////////////////////////////////////////////
  TextureManager* _textureManager;               ///< Le gestionnarie de textures
  FontManager*    _fontManager;                  ///< Le gestionnaire de polices
  PanelPions      _panelPions;                   ///< Les pions disponibles
  std::vector<PionDrawable> _pionsDChoosen;      ///< Réprésentation graphique de la sélection courante
  std::vector<Pion> _pionsChoosen;               ///< Représentation métier de la sélection courante
  int _indexNextPion;                            ///< L'index du pion suivant à placer  
  sf::RectangleShape _backgroundChoosenCoins;    ///< Le fond de la sélection courante
  Button _resetButton;                           ///< Le bouton de reset
  std::vector<Pion> _pionValidated;              ///< La sélection validée
  std::vector<CorrectionDrawable> _correctionsD; ///< La correction sous forme graphique
  std::vector<PionDrawable> _combinaisonsD;      ///< Les combinaisons du plateau sour forme graphique
};

#endif // BOARD_HPP_

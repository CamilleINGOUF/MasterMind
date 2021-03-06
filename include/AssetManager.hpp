#ifndef ASSET_MANAGER_HPP_
#define ASSET_MANAGER_HPP_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

////////////////////////////////////////////////////////////
/// \brief Gestion des ressources (Textures, Sounds, Music, ...)
/// beaucoup plus propre
///
////////////////////////////////////////////////////////////
template<typename Resource, typename Identifier>
class AssetManager
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Chargement d'une ressource
  ///
  /// \param id l'identifiant de la ressource
  /// \param path le chemin d'accès au fichier
  ///
  ////////////////////////////////////////////////////////////
  void load(Identifier id, const std::string& path);

  ////////////////////////////////////////////////////////////
  /// \brief Retourne la ressource associée à l'identifiant
  /// ou nullptr
  ///
  /// \param id l'identifiant de la ressource
  ///
  ///////////////////////////////////////////////////////////
  Resource& get(Identifier id);

  ////////////////////////////////////////////////////////////
  /// \brief Retourne la ressource associée à l'identifiant
  ///
  /// \param id l'identifiant de la ressource
  ///
  ///////////////////////////////////////////////////////////
  const Resource& get(Identifier id) const;
private:

  void addResource(Identifier id, std::unique_ptr<Resource> resource);
  
  ///////////////////////////////////////////////////////////
  /// Données membres
  ///////////////////////////////////////////////////////////
  std::map<Identifier, std::unique_ptr<Resource>> _resources; ///< Mappage des ressources
};

#include "AssetManager.inl"

#endif // ASSET_MANAGER_HPP_

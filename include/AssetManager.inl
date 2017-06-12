////////////////////////////////////////////////////////////
template<typename Resource, typename Identifier>
void AssetManager<Resource, Identifier>::load(Identifier id,
     const std::string& path)
{
     std::unique_ptr<Resource> resource = std::make_unique<Resource>();
     if (!resource->loadFromFile(path))
     {
     	throw std::runtime_error("Impossible de charger la ressource " + path);
     }
     addResource(id, std::move(resource));
}


////////////////////////////////////////////////////////////
template<typename Resource, typename Identifier>
Resource& AssetManager<Resource, Identifier>::get(Identifier id)
{
	auto resource = _resources.find(id);
	assert(resource != _resources.end());
	return *resource->second;
}



////////////////////////////////////////////////////////////
template<typename Resource, typename Identifier>
const Resource& AssetManager<Resource, Identifier>::get(Identifier id) const
{
	auto resource = _resources.find(id);
	assert(resource != _resources.end());
	return *resource->second;
}


////////////////////////////////////////////////////////////
template<typename Resource, typename Identifier>
void AssetManager<Resource, Identifier>::addResource(Identifier id,
     std::unique_ptr<Resource> resource)
{
	auto inserted = _resources.insert(std::make_pair(id,
	     std::move(resource)));
	assert(inserted.second);
}
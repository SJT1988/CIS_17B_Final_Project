#include "AssetManager.h"

AssetManager::AssetManager(Manager * man)
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::AddTexture(std::string id, const char * path)
{
	// Load texture will return an SDL pointer to the texture file
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture * AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

#include "TextureManager.h"



SDL_Texture *TextureManager::LoadTexture(const char *texture)
{
	SDL_Surface *tempSurface = IMG_Load(texture);
	SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	// SDL_RenderCopy(Game::renderer, tex, &src, &dest);

	// RenderCopyEx() has same features plus 3 more for transforming texture: *angle, center, flip
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}
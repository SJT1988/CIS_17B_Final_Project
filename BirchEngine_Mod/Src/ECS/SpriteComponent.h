#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"

#include "Constants.h"

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int numFrames = 0;
	int delay = 100; // milliseconds

public:
	SpriteComponent() = default;
	
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	SpriteComponent(const char* path, int mNumFrames, int mDelay)
	{
		animated = true;
		numFrames = mNumFrames;
		delay = mDelay;
		setTexture(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / delay) % numFrames);
		}
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
		destRect.w = transform->width*transform->scale;
		destRect.h = transform->height*transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};
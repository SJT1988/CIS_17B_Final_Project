#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>

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

	int animIndex = 0;

	// create a mapping between indices and Animations
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;

		// create animations --> Animation(index, #frames in animation, delay between frames):
		Animation player_idleUp = Animation(0, 1, 1); // IdleUp pose is index 0, 1 frame long, and has a 1 second delay
		Animation player_idleDown = Animation(1, 1, 1);
		Animation player_idleLeft = Animation(2, 1, 1);
		Animation player_idleRight = Animation(3, 1, 1);

		Animation player_walkUp = Animation(4, 4, 100);
		Animation player_walkDown = Animation(5, 4, 100);
		Animation player_walkLeft = Animation(6, 4, 100);
		Animation player_walkRight = Animation(7, 4, 100);

		animations.emplace("IdleUp", player_idleUp);
		animations.emplace("IdleDown", player_idleDown);
		animations.emplace("IdleLeft", player_idleLeft);
		animations.emplace("IdleRight", player_idleRight);
		animations.emplace("WalkUp", player_walkUp);
		animations.emplace("WalkDown", player_walkDown);
		animations.emplace("WalkLeft", player_walkLeft);
		animations.emplace("WalkRight", player_walkRight);

		Play("IdleDown");

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

		/* Multiple-frame animations will have their animations
		indexed by the y-pixel-position of the source rectangle's
		upper-left corner in the spritemap. In our case, that will
		be integral multiples of the TILE_SIZE (32px),
		eg. 0, 32, 64, etc.*/
		srcRect.y = animIndex * transform->height;

		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
		destRect.w = transform->width*transform->scale;
		destRect.h = transform->height*transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animationName)
	{
		numFrames = animations[animationName].frames;
		animIndex = animations[animationName].index;
		delay = animations[animationName].delay;
	}
};
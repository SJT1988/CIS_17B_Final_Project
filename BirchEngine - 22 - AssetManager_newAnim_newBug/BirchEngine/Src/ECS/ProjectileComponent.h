#pragma once

#include "ECS.h"
#include "Components.h"

class ProjectileComponent : public Component
{
public:
	/*
	Constructor for a Projectile Component.
		rng:	How far a projectile can go before it is destroyed.
		sp:		The speed of the projectile.
	*/
	ProjectileComponent(int rng, int sp) 
	{
		this->range = rng;
		this->speed = sp;
	}

	~ProjectileComponent() {};

	void init() override 
	{
		transform = &entity->getComponent<TransformComponent>();
	}
	void update() override
	{
		distance += speed;

		if (distance > range)
		{
			entity->destroy();
		}
		else if (transform->position.x > 352 /* Game::camera.x + Game::camera.w */ ||
			transform->position.x < 0 /* Game::camera.x */ ||
			transform->position.y > 352 /* Game::camera.y + Game::camera.h */ ||
			transform->position.y < 0 /* Game::camera.y */
			)
		{
			entity->destroy();
		}
	}
private:
	TransformComponent* transform;

	// how far the projectile can go before being destroyed
	int range = 0;
	// speed of the projectile
	int speed = 0;
	// counter for how far the projectile has travelled
	int distance = 0;
};
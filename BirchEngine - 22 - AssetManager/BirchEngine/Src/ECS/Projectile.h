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
	}
private:
	TransformComponent* transform;

	// how far the projectile can go before being destroyed
	int range;
	// speed of the projectile
	int speed;
	// counter for how far the projectile has travelled
	int distance;
};
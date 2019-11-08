#pragma once
#include <SDL.h>

class Collision
{
public:

	/*
	AABB: "Axis-Aligned Bounding Box".
	This method is exclusively for rectangles whose
	orientations align with the cartestian coordinate system.
	We essentially just check whether corresponding sides
	overlap on their respective axes.
	*/
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};
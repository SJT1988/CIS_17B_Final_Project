#pragma once
#include "Game.h"

class Map
{
public:
	Map();
	~Map();

	void LoadMap(int arr[11][11]);
	void DrawMap();

private:

	SDL_Rect src, dest;

	SDL_Texture *floor;
	SDL_Texture *bricks;
	SDL_Texture *ladder;

	int map[11][11];
};
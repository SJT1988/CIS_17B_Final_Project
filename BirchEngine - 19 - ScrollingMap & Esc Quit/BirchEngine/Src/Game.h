#pragma once

#include "SDL.h"
#include "SDL_Image.h"

#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
public:

	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static bool isRunning;
	static void AddTile(int srcX, int srcY, int posX, int posY);
	static void AddFX(int srcX, int srcY, int posX, int posY);
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders; // a vector of collider component pointers

private:
	
	//bool isRunning = false;
	int cnt = 0;
	SDL_Window *window;
};
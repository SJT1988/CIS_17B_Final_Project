#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "Constants.h"

Map* sceneMap;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());

// put tiles in the game:

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	assets->AddTexture("terrain", "Assets/tileset.png");
	assets->AddTexture("player", "Assets/RickTanglePI.png");

	sceneMap = new Map("terrain", 1, TILE_SIZE);

	// +----------------------------+
	// | $$$ ECS IMPLEMENTATION $$$ |
	// +----------------------------+

	// background map:
	sceneMap->LoadMap("Assets/map01BG.map", 11, 11, Game::groupMapBG);
	// 'the' map:
	sceneMap->LoadMap("Assets/map01.map", 11, 11, Game::groupMap);
	// transform coordinates are in pixels. Player instantiated at (0,0) by default
	player.addComponent<TransformComponent>(5 * TILE_SIZE, 2 * TILE_SIZE); 
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers); // reminder: player(s) is/are being drawn in Update()

	// fx map/overlays:
	sceneMap->LoadMap("Assets/map01FX.map", 11, 11, groupMapFX);

	// load colliders
	sceneMap->Map::LoadColliders("Assets/map01Colliders.map", 11, 11);
}

auto& mapBgTiles(manager.getGroup(Game::groupMapBG));
auto& mapTiles(manager.getGroup(Game::groupMap));
auto& mapFxTiles(manager.getGroup(Game::groupMapFX));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{

	SDL_Rect playerCollider = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPosition = player.getComponent<TransformComponent>().position;
	std::cout <<  player.getComponent<TransformComponent>().velocity << std::endl;

	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect cCollider = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCollider, playerCollider))
		{
			// if player collides, he is reset to previous position he was in
			player.getComponent<TransformComponent>().position = playerPosition;
		}
	}
}

void Game::render()
{
	//start with this
	SDL_RenderClear(renderer);
	//manager.draw(); // this would draw objects in the order they were created in. We don't want this anymore.
	
	//first draw all the tiles:
	for (auto& t : mapBgTiles)
	{
		t->draw();
	}
	for (auto& t : mapTiles)
	{
		t->draw();
	}
	// DEBUG ONLY:
	/*
	for (auto& c : colliders)
	{
		c->draw();
	}
	*/
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& t : mapFxTiles)
	{
		t->draw();
	}
	//end with this
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

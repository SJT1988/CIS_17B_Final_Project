#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

#include "Constants.h"

Map *mapBG, *map, *mapFX;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto&wall(manager.addEntity());

const char* tileSet = "Assets/tileset.png";

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders,
	groupNPCs
};

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

	mapBG = new Map();
	map = new Map();
	mapFX = new Map();

	// +----------------------------+
	// | $$$ ECS IMPLEMENTATION $$$ |
	// +----------------------------+

	// background map:
	map->LoadMap("Assets/mapBG.map", 11, 11);
	// 'the' map:
	map->LoadMap("Assets/map01.map", 11, 11);
	// transform coordinates are in pixels if you use them. Default is 0,0
	player.addComponent<TransformComponent>(5 * TILE_SIZE, 3 * TILE_SIZE); // putting a new coordinate here works now
	// 4 frames in animation, animate continuously with 1 sec between frames:
	player.addComponent<SpriteComponent>("Assets/RexTangle.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers); // reminder: player(s) is/are being drawn in Update()

	/* 
	LIMITATION:
		THE LAST THING THAT GETS DRAWN IN UPDATE() is the player.
		As of now, there is not a method to render on top of the player
		without updating the foreground every frame. Running the next
		line after player(s) have been drawn in Update() will bring the
		program to a terrifying crawl. DO NOT TRY IT.
		Since the player is drawn in Update(), it doesn't matter if we do
		this line here for before all the "player" stuff above.
	*/
	// fx map/overlays:
	mapFX->LoadMap("Assets/mapFX.map", 11, 11);

	/*
	wall.addComponent<TransformComponent>(5*TILE_SIZE, 5*TILE_SIZE, TILE_SIZE, TILE_SIZE, 1);
	wall.addComponent<SpriteComponent>("Assets/bricks.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);
	*/
}

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
	manager.refresh();
	manager.update();

	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies)); // TODO: enemies
auto& npcs(manager.getGroup(groupNPCs)); // TODO: NPCs

void Game::render()
{
	//start with this
	SDL_RenderClear(renderer);
	//manager.draw(); // this would draw objects in the order they were created in. We don't want this anymore.
	
	//first draw all the tiles:
	for (auto& t : tiles)
	{
		t->draw();
	}
	// IDEA: refactor players, enemies, npcs as "actors" or further group under "actors"
	//then draw the player(s):
	for (auto& p : players)
	{
		p->draw();
	}
	//then draw the enemies:
	for (auto& e : enemies)
	{
		e->draw();
	}
	//then draw the npcs:
	for (auto& n : npcs)
	{
		n->draw();
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

void Game::AddTile(int srcX, int srcY, int posX, int posY)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY,posX, posY, tileSet);
	tile.addGroup(groupMap);
}

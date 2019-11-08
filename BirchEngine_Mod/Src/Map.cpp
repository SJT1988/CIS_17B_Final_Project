#include "Map.h"
#include "TextureManager.h"

int level_00[11][11] =
{
	{1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,2,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,1,},
	{1,1,1,1,1,1,1,1,1,1,1}
};

Map::Map()
{
	floor = TextureManager::LoadTexture("Assets/floor.png"); // 0
	bricks = TextureManager::LoadTexture("Assets/bricks.png"); // 1
	ladder = TextureManager::LoadTexture("Assets/ladder.png"); // 2
	
	LoadMap(level_00);

	src.x = dest.x = 0;
	src.y = dest.y = 0;
	src.w = dest.w = TILE_SIZE;
	src.h = dest.h = TILE_SIZE;

}

Map::~Map()
{
	SDL_DestroyTexture(floor);
	SDL_DestroyTexture(bricks);
	SDL_DestroyTexture(ladder);
}

void Map::LoadMap(int arr[11][11])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			map[i][j] = arr[i][j];
		}
	}
}

void Map::DrawMap()
{
	int type = 0;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			type = map[i][j];

			dest.x = TILE_SIZE * j;
			dest.y = TILE_SIZE * i;

			switch (type)
			{
				case 0:
					TextureManager::Draw(floor, src, dest);
					break;
				case 1:
					TextureManager::Draw(bricks, src, dest);
					break;
				case 2:
					TextureManager::Draw(ladder, src, dest);
					break;
				default:
					break;
			}
		}
	}
}

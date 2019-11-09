#include "Map.h"
#include "Game.h"
#include <fstream>

#include "Constants.h"

Map::Map()
{

}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			// id must be int and atoi() converts string to int:
			Game::AddTile(atoi(&tile), x * TILE_SIZE, y * TILE_SIZE);
			mapFile.ignore(); //ignore the comma
		}
	}

	mapFile.close();
}



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
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	// these loops parse the .map file:
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			srcY = atoi(&c)*TILE_SIZE; // atoi := string-to-int
			mapFile.get(c);
			srcX = atoi(&c)*TILE_SIZE;
			Game::AddTile(srcX, srcY, x*TILE_SIZE, y*TILE_SIZE);
			mapFile.ignore(); //skip the comma
		}
	}

	mapFile.close();
}


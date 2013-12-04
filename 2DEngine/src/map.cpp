#include <iostream>
#include <fstream>
#include <string>

#include "../include/map.h"
#include "../include/game.h"

Map::Map(){
}

Map::Map(string mapFilePath){
	string line;

	//Open the map file
	ifstream mapFile(mapFilePath.c_str());

	if (mapFile.is_open()){
		//Read height and width of map.
		getline(mapFile, line);
		mapHeight = atoi(line.c_str());
		getline(mapFile, line);
		mapWidth = atoi(line.c_str());

		grid = new int*[mapWidth];

		for (int row = 0; row < mapHeight; row++) {
			grid[row] = new int[mapWidth];
		}

		for (int row = 0; row < mapHeight; row++)
		{
			getline(mapFile, line);
			char mapTiles[1000];
			strcpy_s(mapTiles, line.c_str());

			for (int col = 0; col < mapWidth; col++)
			{
				//Integer conversion
				grid[row][col] = mapTiles[col] - 48;
			}
		}
	}
	else
	{
		cerr << SDL_GetError() << endl;
	}
}

int** Map::getMap()
{
	return grid;
}

int Map::getTile(int x, int y)
{
	// Checks if the pixel is within the map.
	if (x > mapWidth * TILE_WIDTH || x < 0) {
		return TILE_SOLID;
	}
	if (y > mapHeight * TILE_HEIGHT || y < 0) {
		return TILE_SOLID;
	}

	int tileX = (x - (TILE_WIDTH / 2)) / TILE_WIDTH;
	int tileY = (y - (TILE_HEIGHT / 2)) / TILE_HEIGHT;

	if (grid[tileY][tileX] == 1) {
		return TILE_SOLID;
	}
	if (grid[tileY][tileX] == 2){
		return TILE_GOAL;
	}

	return TILE_EMPTY;
}

SDL_Rect Map::getPlayerSpawn()
{
	SDL_Rect spawn;
	spawn.x = 300;
	spawn.y = 300;

	for (int row = 0; row < mapHeight; row++) {
		for (int col = 0; col < mapWidth; col++) {
			if (grid[row][col] == 3) {
				spawn.y = row * TILE_HEIGHT + 20;
				spawn.x = col * TILE_WIDTH;
			}
		}
	}

	return spawn;
}

int Map::getHeight()
{
	return mapHeight;
}

int Map::getWidth()
{
	return mapWidth;
}
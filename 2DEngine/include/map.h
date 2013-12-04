#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <list>
#include <tuple>
#include <SDL.h>
using namespace std;

/**
*  The level of the game.
*/
class Map{
public:
	Map();

	/**
	Initialises the map from a file.
	*/
	Map(string mapFilePath);

	/**
		Gets the map in tiles.
	*/
	int** getMap();

	/**
		Gets the height of the map in tiles.
		@return The height of the map in tiles.
	*/
	int getHeight();
	/**
		Gets the width of the map in tiles.
		@return The width of the map in tiles.
	*/
	int getWidth();

	/**
		Gets the tile in the tile map represented by the given pixel.
	*/
	int getTile(int xPixel, int yPixel);

	/**
		Gets the spawn position of the player.
	*/
	SDL_Rect getPlayerSpawn();

private:
	int mapHeight;
	int mapWidth;
	int** grid;
	
};

#endif
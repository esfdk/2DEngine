#ifndef ENGINESETTINGS_H
#define ENGINESETTINGS_H

#include<SDL.h>

class EngineSettings{
public:
	#define GAME_NAME "2D Platformer"

	#pragma region Level Variables
	// Text file to load map from
	#define MAP_TO_LOAD "levels/Level0.txt"

	// Tile sizes
	#define TILE_HEIGHT 64
	#define TILE_WIDTH 64
	// Tile textures 
	// Source: http://www.creativecrash.com/system/photos/000/292/579/292579/watermarked/Overview-64-textures.jpg
	#define SOLID_BLOCK_TEXTURE "Textures/RedBlock.png"
	#define GOAL_BLOCK_TEXTURE "Textures/GreyBlock.png" 

	#define COLLISION_POINT_AMOUNT 9

	// Tile types
	#define TILE_EMPTY 0
	#define TILE_SOLID 1
	#define TILE_GOAL 2
	
	/**
	* Max amount of enemies
	*/
	#define MAX_AMOUNT_OF_ENEMIES 100
	/**
	* Gravity (how much characters fall (in pixels) per game loop).
	*/
	#define GRAVITY 7
	#pragma endregion
};
#endif
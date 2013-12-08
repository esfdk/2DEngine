#ifndef ENGINESETTINGS_H
#define ENGINESETTINGS_H

#include<SDL.h>

class EngineSettings{
public:
	#pragma region Game Settings
	#define GAME_NAME "2D Platformer"

	#define WINDOW_HEIGHT 768
	#define WINDOW_WIDTH 1280

	// Highest amount of animations clips ()
	#define MAX_ANIMATION_CLIPS 13

	// Win text
	#define WIN_TEXT "You have completed the level!"

	// Loss text
	#define LOSS_TEXT "You have died!"

	// Max amount of enemies that can spawn in a level
	#define MAX_AMOUNT_OF_ENEMIES 100
	#pragma endregion

	#pragma region Controls
	// Jump key
	#define JUMP_KEY SDLK_w
	#define JUMP_KEY_SCANCODE SDL_SCANCODE_W
	// Move left key
	#define WALK_LEFT_KEY SDLK_a
	#define WALK_LEFT_KEY_SCANCODE SDL_SCANCODE_A
	// Move right key
	#define WALK_RIGHT_KEY SDLK_d
	#define WALK_RIGHT_KEY_SCANCODE SDL_SCANCODE_D
	// Quit key
	#define QUIT_GAME_KEY_SCANCODE SDL_SCANCODE_ESCAPE
	// Skip end screen key
	#define SKIP_ENDSCREEN_KEY_SCANCODE SDL_SCANCODE_SPACE
	#pragma endregion

	#pragma region Level Variables
	// Text file to load map from
	#define MAP_TO_LOAD "levels/Level0.txt"

	// Tile sizes
	#define TILE_HEIGHT 64
	#define TILE_WIDTH 64
	// Tile textures 
	// Source: http://www.creativecrash.com/system/photos/000/292/579/292579/watermarked/Overview-64-textures.jpg
	#define SOLID_BLOCK_TEXTURE "Textures/SolidTile.png"
	#define GOAL_BLOCK_TEXTURE "Textures/GoalTile.png" 
	#pragma endregion

	// Tile types
	#define TILE_EMPTY 0
	#define TILE_SOLID 1
	#define TILE_GOAL 2
	
	// Gravity (how much characters fall (in pixels) per game loop).
	#define GRAVITY 7
	#pragma endregion

	#pragma region Player variables
	//Textures
	#define PLAYER_STAND_TEXTURE "Textures/PlayerStand.png"
	#define PLAYER_JUMP_TEXTURE "Textures/PlayerJump.png"
	#define PLAYER_RUN_TEXTURE "Textures/PlayerRunning.png"
	#define PLAYER_RUN_CLIP_COUNT 10

	/**
	The speed the player moves with.
	*/
	#define PLAYER_SPEED 7
	#pragma endregion
};
#endif
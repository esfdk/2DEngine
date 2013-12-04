#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "../include/Window.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/xMonster.h"
#include "../include/yMonster.h"

class Game{
public:
	#pragma region Game variables
	//Text file to load map from
	#define MAP_TO_LOAD "levels/Level0.txt"

	//Win/loss events
	SDL_Event winEvent;
	SDL_Event lossEvent;
	#define WIN_EVENT_CODE 1
	#define LOSS_EVENT_CODE 2

	// Tile sizes
	#define TILE_HEIGHT 64
	#define TILE_WIDTH 64

	//Tile types
	#define TILE_EMPTY 0
	#define TILE_SOLID 1
	#define TILE_GOAL 2

	//Move states and gravity
	/**
		Stands still, looking to the right.
	*/
	#define STAND_RIGHT 1
	/**
		Stands still, looking to the left.
	*/
	#define STAND_LEFT -1
	/**
		Moving to the right.
	*/
	#define MOVE_RIGHT 2
	/**
		Moving to the left.
	*/
	#define MOVE_LEFT -2
	/**
		Gravity (how much characters fall (in pixels) per game loop).
	*/
	#define GRAVITY 7
	#pragma endregion

	#pragma region Player variables
	//Textures
	#define PLAYER_STAND_TEXTURE "Textures/PlayerStandLeft.png"
	#define PLAYER_JUMP_TEXTURE "Textures/PlayerJump.png"
	#define PLAYER_RUN_TEXTURE "Textures/PlayerRunning.png"

	/**
		The speed the player moves with.
	*/
	#define PLAYER_SPEED 7
	
	#pragma endregion

	#pragma region Monster variables
	//Enemy types
	#define MONSTER_WALKING 6
	#define MONSTER_FLYING 7

	//Enemy textures
	#define X_MONSTER_RUN_TEXTURE "Textures/WalkingMonster.png"
	#define Y_MONSTER_TEXTURE "Textures/FlyingMonster.png"
	/**
		The speed the enemies move with.
	*/
	#define MONSTER_SPEED 5
	#pragma endregion

#pragma region main and game loop

	/**
		Initializes the game.
	*/
	int init();
	/**
		The game loop.
	*/
	void gameLoop();
#pragma endregion
private:
	#pragma region Keys
	/**
		Keys currently pressed down.
	*/
	int horizontalKeyPressed, verticalKeyPressed;

	/**
		The state of keys on the keyboard.
	*/
	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
	#pragma endregion

#pragma region Game elements
	/**
		The map.
	*/
	Map map;
	/**
		The player.
	*/
	Player player;
	/**
		Array of monsters.
	*/
	xMonster* xMonsters;
	yMonster* yMonsters;
	int numberOfXMonsters;
	int numberOfYMonsters;
#pragma endregion

#pragma region GameLogic
	/**
		Moves the player.
	*/
	void movePlayer();
	/**
		Moves a walking monster.
	*/
	xMonster moveWalking(xMonster m);
	/**
		Moves a flying monster.
	*/
	yMonster moveFlying(yMonster m);
	/**
		Updates player character.
	*/
	void updatePlayer();
	/**
		Loads enemies from the map.
	*/
	void loadMonsters();
	/**
		Update enemy positions.
	*/
	void updateEnemies();
	/**
		Checks for player collision.
	*/
	bool checkPlayerCollision(int newXPos, int newYPos);

	/**
		Checks for collision with walls.
	*/
	bool checkMonsterCollision(int newXPos, int newYPos, int textureWidth, int textureHeight);

	/**
		Gets temporary collision points for a texture.
	*/
	void getCollisionPoints(int newXPos, int newYPos, int textureWidth, int textureHeight, SDL_Point* collisionPoints);
#pragma endregion


#pragma region Draw elements
	/**
		Stone block texture (64x64 pixels)
	*/
	SDL_Texture *stoneBlock; // Source: http://www.creativecrash.com/system/photos/000/292/579/292579/watermarked/Overview-64-textures.jpg
	/**
		Bricks texture (64x64 pixels)
	*/
	SDL_Texture *bricks; // Source: http://www.creativecrash.com/system/photos/000/292/579/292579/watermarked/Overview-64-textures.jpg
	/**
		Grass texture (64x64 pixels)
	*/
	SDL_Texture *grass; // Source: http://www.creativecrash.com/system/photos/000/292/579/292579/watermarked/Overview-64-textures.jpg

	/**
		Position of camera
	*/
	int camPosX;
#pragma endregion

#pragma region Draw methods
	/**
		Draws the level.
	*/
	void drawLevel();
	/**
		Draws the player.
	*/
	void drawPlayer();
	/**
		Draws enemies.
	*/
	void drawEnemies();

	/**
		Draws a win screen when the player wins.
	*/
	void Game::drawWinScreen();

	/**
		Draws a loss screen when the player loses.
	*/
	void Game::drawLossScreen();
#pragma endregion
};
#endif 
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "../include/Window.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/Enemy.h"
#include "../include/EngineSettings.h"
#include "../include/helperClass.h"
#include "../include/EnemyTypes.h"

class Game{
public:	
	#pragma region main game functions
	/**
	* Initializes the game.
	*/
	int init();
	/**
	* The game loop.
	*/
	void gameLoop();
	/**
	* Ends the game.
	*/
	void endGame();
#pragma endregion
private:
	#pragma region Keys
	/**
	* Keys currently pressed down.
	*/
	int horizontalKeyPressed, verticalKeyPressed;

	/**
	* The state of keys on the keyboard.
	*/
	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
	#pragma endregion

#pragma region Game elements
	/**
	* The map.
	*/
	Map map;
	/**
	* The player.
	*/
	Player player;
	/**
	* List of enemies.
	*/
	Enemy *enemies[MAX_AMOUNT_OF_ENEMIES];
	/**
	* Number of enemies in the map
	*/
	int numberOfEnemies;
#pragma endregion

#pragma region GameLogic
	/**
	* Loads enemies from the map.
	*/
	void loadEnemies();
	
	/**
	* Updates player character.
	*/
	void updatePlayer();
	
	/**
	* Update enemy positions.
	*/
	void updateEnemies();
#pragma endregion


#pragma region Draw elements
	/**
	* Stone block texture
	*/
	SDL_Texture *solidBlockTexture;
	/**
	* Goal texture
	*/
	SDL_Texture *goalTexture;
	/**
	* Position of camera
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
#pragma endregion
};
#endif 
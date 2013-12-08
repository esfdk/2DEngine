#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <SDL.h>
#include "../include/game.h"

using namespace std;

/**
	Initialises the game.
*/
int Game::init(){
	try {
		Window::Init(GAME_NAME);
	}
	catch (const std::runtime_error &e){
		std::cout << e.what() << std::endl;
		Window::Quit();
		return -1;
	}
	
	//Textures
	solidBlockTexture = Window::LoadImage(SOLID_BLOCK_TEXTURE);
	goalTexture = Window::LoadImage(GOAL_BLOCK_TEXTURE);

	map = Map(MAP_TO_LOAD);

	player = Player(map.getPlayerSpawn().x, map.getPlayerSpawn().y);

	loadEnemies();

	HelperClass::winEvent.type = SDL_USEREVENT;
	HelperClass::winEvent.user.code = WIN_EVENT_CODE;

	HelperClass::lossEvent.type = SDL_USEREVENT;
	HelperClass::lossEvent.user.code = LOSS_EVENT_CODE;
	
	gameLoop();

	return 0;
}

/** 
	Main game loop. 
*/
void Game::gameLoop(){
	SDL_Event e;
	bool quit = false;	
	bool showVictoryScreen = false;
	bool showLossScreen = false;

	while (!quit)
	{
		//// Event Polling
		while (SDL_PollEvent(&e))
		{
			// Update keyboardState
			SDL_PumpEvents();

			// If user closes the window
			if (e.type == SDL_QUIT){
				quit = true;
			}

			if (e.type == SDL_USEREVENT){
				if (e.user.code == WIN_EVENT_CODE){
					showVictoryScreen = true;
				}

				if (e.user.code == LOSS_EVENT_CODE){
					showLossScreen = true;
				}
			}

			horizontalKeyPressed = 0;
			verticalKeyPressed = 0;

			if (keyboardState[QUIT_GAME_KEY_SCANCODE])
			{
				quit = true;
			}

			if (showVictoryScreen || showLossScreen)
			{
				if (keyboardState[SKIP_ENDSCREEN_KEY_SCANCODE])
				{
					endGame();
				}
			}
			else
			{
				if (keyboardState[WALK_RIGHT_KEY_SCANCODE])
				{
					player.accelerateX();
					player.moveState = MOVE_RIGHT;
					horizontalKeyPressed = WALK_RIGHT_KEY;
				}
				if (keyboardState[WALK_LEFT_KEY_SCANCODE])
				{
					player.accelerateX();
					player.moveState = MOVE_LEFT;
					horizontalKeyPressed = WALK_LEFT_KEY;
				}
				if (keyboardState[JUMP_KEY_SCANCODE])
				{
					player.accelerateY();
					verticalKeyPressed = JUMP_KEY;
				}
			}
		}

		if (showVictoryScreen)
		{
			Window::Clear();
			HelperClass::drawWinScreen();
			Window::Present();
		}
		else if (showLossScreen)
		{
			Window::Clear();
			HelperClass::drawLossScreen();
			Window::Present();
		}
		else
		{
			updatePlayer();
			updateEnemies();

			Window::Clear();
			drawLevel();
			drawPlayer();
			drawEnemies();
			Window::Present();
		}
    }

	endGame();
}

void Game::endGame()
{
	Window::Clear();
	Window::Quit();
	exit(0);
}


/**
Loads monsters from the map.
*/
void Game::loadEnemies(){
	int** tempMap = map.getMap();

	//Create the enemies
	this->numberOfEnemies = 0;

	for (int row = 0; row < map.getHeight(); row++) 
	{
		for (int col = 0; col < map.getWidth(); col++) 
		{
			if (tempMap[row][col] == ENEMY_DEMON)
			{
				Demon *newEnemy = new Demon(col * TILE_HEIGHT, row * TILE_HEIGHT);
				enemies[numberOfEnemies] = newEnemy;
				this->numberOfEnemies++;
			}
			if (tempMap[row][col] == ENEMY_COPTER) {
				Copter *newEnemy = new Copter(col * TILE_HEIGHT, row * TILE_HEIGHT);
				enemies[numberOfEnemies] = newEnemy;
				this->numberOfEnemies++;
			}
		}
	}
}

void Game::updatePlayer()
{
	// If a or d is not pressed, decelerate on x.
	if (horizontalKeyPressed == 0){
		player.decelerateX();
	}
	// If w is not pressed, decelerate on y.
	if (verticalKeyPressed == 0){
		player.decelerateY();
	}

	player.move(map, enemies, numberOfEnemies);
	player.updateTexture();
}


/**
	Update enemy positions.
*/
void Game::updateEnemies()
{
	for (int enemy = 0; enemy < numberOfEnemies; enemy++)
	{
		Enemy *tempEnemy = enemies[enemy];
		tempEnemy->updateTexture();
		tempEnemy->move(map);
	}
}

/**
	Draws the level.
*/
void Game::drawLevel(){

	int** tileMap = map.getMap();
	int firstX, offsetX;
	int height = map.getHeight(), width = map.getWidth();

	// Camera - makes sure we only draw inside the map.
	camPosX = (player.xPos) - (WINDOW_WIDTH / 2);
	if (camPosX < 0) camPosX = 0;
	if (camPosX + WINDOW_WIDTH > width * TILE_WIDTH) camPosX = (map.getWidth() * TILE_WIDTH) - WINDOW_WIDTH;

	// Find the first tile to draw and how much of it should be drawn.
	firstX = camPosX / TILE_WIDTH;
	offsetX = camPosX % TILE_WIDTH;

	// Cycle through the tiles in the map, find the first column to draw, draw it, repeat until right edge of screen is reached. 
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++) {
			
			int currentX;
			if (x + firstX < width){ // If end of map is not yet reached.
				currentX = x + firstX;
			}
			else { // If end of map is reached.
				currentX = width - 1;
			}

			// Draw the tile.
			if (tileMap[y][currentX] == 1)
			{
				SDL_Rect pos;
				pos.x = (x * TILE_WIDTH) - (offsetX);
				pos.y = y * TILE_HEIGHT;
				pos.w = TILE_WIDTH;
				pos.h = TILE_HEIGHT;

				Window::Draw(solidBlockTexture, pos);
			}

			// Draw the tile.
			if (tileMap[y][currentX] == 2)
			{
				SDL_Rect pos;
				pos.x = (x * TILE_WIDTH) - (offsetX);
				pos.y = y * TILE_HEIGHT;
				pos.w = TILE_WIDTH;
				pos.h = TILE_HEIGHT;

				Window::Draw(goalTexture, pos);
			}
		}
	}
}

/**
	Draws the player.
*/
void Game::drawPlayer(){
	// Player width and height
	int pHeight = player.textureHeight, pWidth = player.textureWidth;

	// Get player position in the map.
	SDL_Rect pos;
	pos.x = player.xPos - (pWidth / 2) - camPosX;
	pos.y = player.yPos - (pHeight / 2);
	pos.w = pWidth;
	pos.h = pHeight;

	if (player.moveState == STAND_RIGHT || player.moveState == MOVE_RIGHT){
		Window::Draw(player.currentTexture, pos, &player.currentClip(), NULL, NULL, NULL, SDL_FLIP_HORIZONTAL);
	}
	else{
		Window::Draw(player.currentTexture, pos, &player.currentClip());
	}
}

/**
	Draws enemies.
*/
	void Game::drawEnemies()
	{
		for (int i = 0; i < numberOfEnemies; i++)
		{
			SDL_RendererFlip flip = SDL_FLIP_NONE;
		
			Enemy *tempEnemy = enemies[i];
			if (tempEnemy->direction) flip = SDL_FLIP_HORIZONTAL;

			SDL_Rect pos;
			pos.x = tempEnemy->xPos - (tempEnemy->textureWidth / 2) - camPosX;
			pos.y = tempEnemy->yPos - (tempEnemy->textureHeight / 2);
			pos.w = tempEnemy->textureWidth;
			pos.h = tempEnemy->textureHeight;
			SDL_Texture *tempTex = tempEnemy->texture;
			SDL_Rect tempRect = tempEnemy->getCurrentClip();
			

			Window::Draw(tempEnemy->texture, pos, &tempRect, NULL, NULL, NULL, flip);
		}
	}
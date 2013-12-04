#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <SDL.h>

#include "../include/game.h"
#include "../include/window.h"
#include "../include/player.h"
#include "../include/xMonster.h"
#include "../include/yMonster.h"
#include "../include/map.h"

using namespace std;

/**
	Initialises the game.
*/
int Game::init(){
	try {
		Window::Init("2D platformer");
	}
	catch (const std::runtime_error &e){
		std::cout << e.what() << std::endl;
		Window::Quit();
		return -1;
	}
	
	//Textures
	bricks = Window::LoadImage("Textures/RedBlock.png");
	stoneBlock = Window::LoadImage("Textures/GreyBlock.png");

	map = Map(MAP_TO_LOAD);

	player = Player(map.getPlayerSpawn().x, map.getPlayerSpawn().y);

	loadMonsters();

	winEvent.type = SDL_USEREVENT;
	winEvent.user.code = WIN_EVENT_CODE;
	winEvent.user.data1 = 0;
	winEvent.user.data2 = 0;

	lossEvent.type = SDL_USEREVENT;
	lossEvent.user.code = LOSS_EVENT_CODE;
	lossEvent.user.data1 = 0;
	lossEvent.user.data2 = 0;

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

	while (!quit){

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
					quit = true;
					showVictoryScreen = true;
					break;
				}

				if (e.user.code == LOSS_EVENT_CODE){
					quit = true;
					showLossScreen = true;
				}
			}

			horizontalKeyPressed = 0;
			verticalKeyPressed = 0;

			if (keyboardState[SDL_SCANCODE_D]){
				player.accelerateX();
				player.moveState = MOVE_RIGHT;
				horizontalKeyPressed = SDLK_d;
			}
			if (keyboardState[SDL_SCANCODE_A]){
				player.accelerateX();
				player.moveState = MOVE_LEFT;
				horizontalKeyPressed = SDLK_a;
			}
			if (keyboardState[SDL_SCANCODE_W]){
				player.accelerateY();
				verticalKeyPressed = SDLK_w;
			}
			if (keyboardState[SDL_SCANCODE_ESCAPE]){
				quit = true;
			}
		}

		updatePlayer();
		updateEnemies();

		Window::Clear();
		drawLevel();
		drawPlayer();
		drawEnemies();
		Window::Present();
    }

	while (showVictoryScreen)
	{
		while (SDL_PollEvent(&e))
		{
			// Update keyboardState
			SDL_PumpEvents();

			// If user closes the window
			if (e.type == SDL_QUIT) {
				showVictoryScreen = false;
			}

			if (keyboardState[SDL_SCANCODE_SPACE]) {
				showVictoryScreen = false;
			}
		}

		Window::Clear();
		drawWinScreen();
		Window::Present();
	}

	while (showLossScreen)
	{
		while (SDL_PollEvent(&e))
		{
			// Update keyboardState
			SDL_PumpEvents();

			// If user closes the window
			if (e.type == SDL_QUIT) {
				showLossScreen = false;
			}

			if (keyboardState[SDL_SCANCODE_SPACE]) {
				showLossScreen = false;
			}
		}

		Window::Clear();
		drawLossScreen();
		Window::Present();
	}

	Window::Clear();
	Window::Quit();
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

	movePlayer();
	player.updateTexture();
	getCollisionPoints(player.xPos, player.yPos, player.playerTextureWidth, player.playerTextureHeight, player.collisionPoints);
}

void Game::movePlayer()
{
	//Horizontal movement
	if (player.moveState == MOVE_LEFT){
		for (int i = 0; i < player.xVel; i++)
		{
			if (checkPlayerCollision(player.xPos - 1, player.yPos)){
				break;
			}

			player.xPos--;
		}
	}
	if (player.moveState == MOVE_RIGHT){
		for (int i = 0; i < player.xVel; i++)
		{
			if (checkPlayerCollision(player.xPos + 1, player.yPos)){
				break;
			}

			player.xPos++;
		}
	}

	//Vertical movement
	if (player.yVel > 0) {
		for (int i = 0; i < GRAVITY; i++)
		{
			if (checkPlayerCollision(player.xPos, player.yPos - 1)){
				player.decelerateY();
				break;
			}

			player.yPos--;
			player.yVel--;
		}
	}
	else {
		for (int i = player.yVel; i < 0; i++)
		{
			// If the player lands on something, he can jump again.
			if (checkPlayerCollision(player.xPos, player.yPos + 1)){
				player.inAir = false;
				break;
			}

			player.yPos++;
		}
	}
}

/**
	Loads monsters from the map.
*/
void Game::loadMonsters(){
	int** tempMap = map.getMap();
	int xMonsterCount = 0;
	int yMonsterCount = 0;

	// Count number of monsters in the map
	for (int row = 0; row < map.getHeight(); row++) {
		for (int col = 0; col < map.getWidth(); col++) {
			if (tempMap[row][col] == MONSTER_FLYING) {
				yMonsterCount++;
			}
			if (tempMap[row][col] == MONSTER_WALKING){
				xMonsterCount++;
			}
		}
	}

	//Create the enemies
	numberOfXMonsters = 0;
	numberOfYMonsters = 0;
	xMonsters = new xMonster[xMonsterCount];
	yMonsters = new yMonster[yMonsterCount];

	for (int row = 0; row < map.getHeight(); row++) {
		for (int col = 0; col < map.getWidth(); col++) {
			if (tempMap[row][col] == MONSTER_WALKING) {
				xMonsters[numberOfXMonsters] = xMonster(col * TILE_WIDTH, row * TILE_HEIGHT);
				numberOfXMonsters++;
			}
			if (tempMap[row][col] == MONSTER_FLYING) {
				yMonsters[numberOfYMonsters] = yMonster(col * TILE_WIDTH + (33), row * TILE_HEIGHT);
				numberOfYMonsters++;
			}
		}
	}
}

/**
	Update enemy positions.
*/
void Game::updateEnemies()
{
	for (int monster = 0; monster < numberOfXMonsters; monster++){
		xMonsters[monster].updateTexture();
		xMonsters[monster] = moveWalking(xMonsters[monster]);
	}

	for (int monster = 0; monster < numberOfYMonsters; monster++){
		yMonsters[monster].updateTexture();
		yMonsters[monster] = moveFlying(yMonsters[monster]);
	}
}

xMonster Game::moveWalking(xMonster m){
	// Move right or left and turn around if walking into wall.
	for (int movement = 0; movement < MONSTER_SPEED; movement++){
		if (m.direction){ // Going right
			if (checkMonsterCollision(m.xPos + 1, m.yPos, m.textureWidth, m.textureHeight)){
				m.direction = !m.direction;
				break;
			}
			m.xPos++;
		}
		else{ // Going left
			if (checkMonsterCollision(m.xPos - 1, m.yPos, m.textureWidth, m.textureHeight)){
				m.direction = !m.direction;
				break;
			}
			m.xPos--;
		}
	}

	// Make monster fall
	for (int movement = 0; movement < GRAVITY; movement++){
		if (checkMonsterCollision(m.xPos, m.yPos + 1, m.textureWidth, m.textureHeight)){
			break;
		}
		m.yPos++;
	}

	return m;
}

yMonster Game::moveFlying(yMonster m){
	// Move right or left and turn around if walking into wall.
	for (int movement = 0; movement < MONSTER_SPEED; movement++){
		if (m.goingUp){ // Going up
			if (checkMonsterCollision(m.xPos, m.yPos - 1, m.textureWidth, m.textureHeight)){
				m.goingUp = !m.goingUp;
				break;
			}
			m.yPos--;
		}
		else{ // Going down
			if (checkMonsterCollision(m.xPos, m.yPos + 1, m.textureWidth, m.textureHeight)){
				m.goingUp = !m.goingUp;
				break;
			}
			m.yPos++;
		}
	}
	return m;
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

				Window::Draw(bricks, pos);
			}

			// Draw the tile.
			if (tileMap[y][currentX] == 2)
			{
				SDL_Rect pos;
				pos.x = (x * TILE_WIDTH) - (offsetX);
				pos.y = y * TILE_HEIGHT;
				pos.w = TILE_WIDTH;
				pos.h = TILE_HEIGHT;

				Window::Draw(stoneBlock, pos);
			}
		}
	}
}

/**
	Draws the player.
*/
void Game::drawPlayer(){
	// Player width and height
	int pHeight = player.playerTextureHeight, pWidth = player.playerTextureWidth;

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
void Game::drawEnemies(){
	for (int i = 0; i < numberOfXMonsters; i++){
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		
		if (xMonsters[i].direction){
			flip = SDL_FLIP_HORIZONTAL;
		}

		SDL_Rect pos;
		pos.x = xMonsters[i].xPos - (xMonsters[i].textureWidth / 2) - camPosX;
		pos.y = xMonsters[i].yPos - (xMonsters[i].textureHeight / 2);
		pos.w = xMonsters[i].textureWidth;
		pos.h = xMonsters[i].textureHeight;
		Window::Draw(xMonsters[i].monsterTexture, pos, &xMonsters[i].getCurrentClip(),
			NULL, NULL, NULL, flip);
	}

	for (int i = 0; i < numberOfYMonsters; i++){
		SDL_Rect pos;
		pos.x = yMonsters[i].xPos - (yMonsters[i].textureWidth / 2) - camPosX;
		pos.y = yMonsters[i].yPos - (yMonsters[i].textureHeight / 2);
		pos.w = yMonsters[i].textureWidth;
		pos.h = yMonsters[i].textureHeight;
		Window::Draw(yMonsters[i].monsterTexture, pos, &yMonsters[i].getCurrentClip());
	}
}

void Game::getCollisionPoints(int newXPos, int newYPos, int textureWidth, int textureHeight, SDL_Point* collisionPoints)
{
	// Calculate 9 collision points on the texture.
	for (int i = 0; i < 9; i++)
	{
		SDL_Point point;
		point.x = newXPos + ((i / 3) * (textureWidth / 2));
		point.y = newYPos + ((i % 3) * (textureHeight / 2));

		collisionPoints[i] = point;
	}
}

bool Game::checkPlayerCollision(int newXPos, int newYPos){

	SDL_Point tempCollisionPoints[9];
	getCollisionPoints(newXPos, newYPos, player.playerTextureWidth, player.playerTextureHeight, tempCollisionPoints);

	for (int i = 0; i < 9; i++){
		SDL_Point tempPoint = tempCollisionPoints[i];
		
		for (int monster = 0; monster < numberOfXMonsters; monster++){
			xMonster m = xMonsters[monster];

			if (tempPoint.x > m.xPos && tempPoint.x < m.xPos + m.textureWidth
				&& tempPoint.y > m.yPos && tempPoint.y < m.yPos + m.textureHeight){
				SDL_PushEvent(&lossEvent);
			}
		}

		int tile = map.getTile(tempPoint.x, tempPoint.y);
		if (tile == TILE_SOLID){
			return true;
		}
		if (tile == TILE_GOAL){
			SDL_PushEvent(&winEvent);
		}
	}

	return false;
}

bool Game::checkMonsterCollision(int newXPos, int newYPos, int textureWidth, int textureHeight){
	SDL_Point tempCollisionPoints[9];
	getCollisionPoints(newXPos, newYPos, textureWidth, textureHeight, tempCollisionPoints);
	for (int i = 0; i < 9; i++){
		SDL_Point tempPoint = tempCollisionPoints[i];

		if (tempPoint.x > player.xPos && tempPoint.x < player.xPos + player.playerTextureWidth
				&& tempPoint.y > player.yPos && tempPoint.y < player.yPos + player.playerTextureHeight){
				SDL_PushEvent(&lossEvent);
		}
		
		int tile = map.getTile(tempPoint.x, tempPoint.y);
		if (tile == TILE_SOLID) return true;
	}

	return false;
}

/**
	Draws a win screen when the player wins.
*/
void Game::drawWinScreen(){
	SDL_Color white = { 255, 255, 255 };
	SDL_Texture *msgGrats;
	SDL_Rect msgGratsBox;

	msgGrats = Window::RenderText("You have completed the level!", "Textures/FreeSans.ttf", white, 50);

	SDL_QueryTexture(msgGrats, NULL, NULL, &msgGratsBox.w, &msgGratsBox.h);

	msgGratsBox.x = (Window::Box().w / 2) - (msgGratsBox.w / 2);
	msgGratsBox.y = (Window::Box().h / 2) - (msgGratsBox.h / 2) - 25;

	Window::Draw(msgGrats, msgGratsBox);
}

void Game::drawLossScreen(){
	SDL_Color white = { 255, 255, 255 };
	SDL_Texture *msgGrats;
	SDL_Rect msgGratsBox;

	msgGrats = Window::RenderText("You have died!", "Textures/FreeSans.ttf", white, 50);

	SDL_QueryTexture(msgGrats, NULL, NULL, &msgGratsBox.w, &msgGratsBox.h);

	msgGratsBox.x = (Window::Box().w / 2) - (msgGratsBox.w / 2);
	msgGratsBox.y = (Window::Box().h / 2) - (msgGratsBox.h / 2) - 25;

	Window::Draw(msgGrats, msgGratsBox);
}
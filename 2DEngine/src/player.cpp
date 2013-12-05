#include "../include/player.h"
#include "../include/helperClass.h"

Player::Player()
{
}

Player::Player(int x, int y){
	xPos = x;
	yPos = y;
	xVel = 0;
	yVel = 0;
	moveState = STAND_RIGHT;
	canJump = false;
	isJumping = true;

	// Initialize the collision points.
	for (int i = 0; i < 9; i++)
	{
		collisionPoints[i] = SDL_Point{ 0, 0 };
	}

	// Load the player textures
	playerStand = Window::LoadImage(PLAYER_STAND_TEXTURE);
	playerRun = Window::LoadImage(PLAYER_RUN_TEXTURE);
	playerJump = Window::LoadImage(PLAYER_JUMP_TEXTURE);

	// Set default texture
	currentTexture = playerStand;

	// Get size of the default texture
	SDL_QueryTexture(currentTexture, NULL, NULL, &textureWidth, &textureHeight);
	
	currentRunClip = 0;
	internalClipCounter = 0;

	standClip.x = 0;
	standClip.y = 0;
	standClip.w = textureWidth;
	standClip.h = textureHeight;

	jumpClip.x = 0;
	jumpClip.y = 0;
	jumpClip.w = textureWidth;
	jumpClip.h = textureHeight;

	for (int i = 0; i < PLAYER_RUN_CLIP_COUNT; i++)
	{
		animationRunClips[i].x = i * textureWidth;
		animationRunClips[i].y = 0;
		animationRunClips[i].h = textureHeight;
		animationRunClips[i].w = textureWidth;
	}

	textureHeight -= 2;
	textureWidth -= 2;

}

void Player::accelerateX()
{
	xVel= PLAYER_SPEED;
	currentRunClip = 0;
}

void Player::accelerateY()
{
	// If player is not in air, give him high y velocity and set his status to in air.
	if (canJump){
		yVel = 200;
		canJump = false;
		isJumping = true;
	}
}

void Player::decelerateX()
{
	if (xVel > 0){
		xVel--;
		currentRunClip = 0;
	}

	if (moveState == MOVE_RIGHT) {
		moveState = STAND_RIGHT;
	}

	if (moveState == MOVE_LEFT) {
		moveState = STAND_LEFT;
	}
}

void Player::decelerateY()
{
	yVel = -GRAVITY;
}

void Player::updateTexture(){
	//Reset clip counter if necessary, calculate current run clip and increase the clip counter.
	internalClipCounter = internalClipCounter % ((PLAYER_RUN_CLIP_COUNT * 2) - 2);
	currentRunClip = internalClipCounter / 2;
	internalClipCounter++;

	if (isJumping){
			currentTexture = playerJump;
	}
	else{
		if (moveState == STAND_RIGHT || moveState == STAND_LEFT)
		{
			currentTexture = playerStand;
		}
		else
		{
			currentTexture = playerRun;
		}
	}
}

SDL_Rect Player::currentClip(){
	if (isJumping){
		return jumpClip;
	}
	if (moveState == MOVE_RIGHT || moveState == MOVE_LEFT)
	{
		return animationRunClips[currentRunClip];
	}

	return standClip;
}

void Player::move(Map map, Enemy **enemyList, int numberOfEnemies)
{
	//Horizontal movement
	if (moveState == MOVE_LEFT){
		for (int i = 0; i < xVel; i++)
		{
			HelperClass::getCollisionPoints(xPos - 1, yPos, textureWidth, textureHeight, collisionPoints);
			if (checkCollision(map, enemyList, numberOfEnemies)){
				break;
			}

			xPos--;
		}
	}
	if (moveState == MOVE_RIGHT){
		for (int i = 0; i < xVel; i++)
		{
			HelperClass::getCollisionPoints(xPos + 1, yPos, textureWidth, textureHeight, collisionPoints);
			if (checkCollision(map, enemyList, numberOfEnemies)){
				break;
			}

			xPos++;
		}
	}

	//Vertical movement
	if (yVel > 0) {
		for (int i = 0; i < GRAVITY; i++)
		{
			HelperClass::getCollisionPoints(xPos, yPos - 1, textureWidth, textureHeight, collisionPoints);
			if (checkCollision(map, enemyList, numberOfEnemies)){
				decelerateY();
				
				break;
			}

			yPos--;
			yVel--;
		}
	}
	else {
		for (int i = yVel; i < 0; i++)
		{
			canJump = false;
			isJumping = true;
			HelperClass::getCollisionPoints(xPos, yPos + 1, textureWidth, textureHeight, collisionPoints);
			if (checkCollision(map, enemyList, numberOfEnemies)){
				// If the player lands on something, he can jump again.
				isJumping = false;
				canJump = true;
				break;
			}
			
			yPos++;
		}
	}
}

bool Player::checkCollision(Map map, Enemy **enemyList, int numberOfEnemies)
{
	for (int i = 0; i < 9; i++){
		SDL_Point tempPoint = collisionPoints[i];

		for (int enemy = 0; enemy < numberOfEnemies; enemy++)
		{
			Enemy *e = enemyList[enemy];

			if (tempPoint.x > e->xPos && tempPoint.x < e->xPos + e->width
				&& tempPoint.y > e->yPos && tempPoint.y < e->yPos + e->height)
			{
				SDL_PushEvent(&HelperClass::lossEvent);
			}
		}
		
		int tile = map.getTile(tempPoint.x, tempPoint.y);

		if (tile == TILE_SOLID)
		{
			return true;
		}

		if (tile == TILE_GOAL){
			SDL_PushEvent(&HelperClass::winEvent);
		}
		
	}
	return false;
}
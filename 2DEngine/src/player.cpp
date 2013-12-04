#include "../include/player.h"
#include "../include/game.h"

Player::Player(){
	
}

Player::Player(int x, int y){
	xPos = x;
	yPos = y;
	xVel = 0;
	yVel = 0;
	moveState = STAND_RIGHT;
	inAir = true;

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
	SDL_QueryTexture(currentTexture, NULL, NULL, &playerTextureWidth, &playerTextureHeight);
	
	currentRunClip = 0;
	internalClipCounter = 0;

	standClip.x = 0;
	standClip.y = 0;
	standClip.w = playerTextureWidth;
	standClip.h = playerTextureHeight;

	jumpClip.x = 0;
	jumpClip.y = 0;
	jumpClip.w = playerTextureWidth;
	jumpClip.h = playerTextureHeight;

	for (int i = 0; i < 10; i++)
	{
		animationRunClips[i].x = i * playerTextureWidth;
		animationRunClips[i].y = 0;
		animationRunClips[i].h = playerTextureHeight;
		animationRunClips[i].w = playerTextureWidth;
	}

	playerTextureHeight -= 2;
	playerTextureWidth -= 2;

}

void Player::accelerateX()
{
	xVel= PLAYER_SPEED;
	currentRunClip = 0;
}

void Player::accelerateY()
{
	// If player is not in air, give him high y velocity and set his status to in air.
	if (!inAir){
		yVel = 200;
		inAir = true;
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
	internalClipCounter = internalClipCounter % 18;
	currentRunClip = internalClipCounter / 2;
	internalClipCounter++;

	if (inAir){
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
	if (inAir){
		return jumpClip;
	}
	if (moveState == MOVE_RIGHT || moveState == MOVE_LEFT)
	{
		return animationRunClips[currentRunClip];
	}

	return standClip;
}
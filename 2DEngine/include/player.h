#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
/**
	The player character.
*/
class Player{
public:
#pragma region Constructors
	/**
		Starts player at x = 300, y = 300.
	*/
	Player();

	/**
		Starts player at given position.
		@param xPixel The x pixel to start player at.
		@param yPixel The y pixel to start player at.
	*/
	Player(int xPixel, int yPixel);

	~Player(){};
#pragma endregion

#pragma region Player textures and methods
	/**
	The texture that shows the player standing still.
	*/
	SDL_Texture *playerStand;
	/**
	The texture that shows the player running.
	*/
	SDL_Texture *playerRun;
	/**
	The texture that shows the player jumping.
	*/
	SDL_Texture *playerJump;
	/**
		The texture currently used to draw the player.
		@return The texture currently in use.
	*/
	SDL_Texture *currentTexture;
	/**
		The clip of the texture currently used.
		@return The rectangle indicating where to clip the currentTexture.
	*/
	SDL_Rect currentClip();

	/**
		The size of the player texture.
		*/
	int playerTextureHeight, playerTextureWidth;

	/**
		Increases clip counter by 1.
		*/
	void increaseClipCounter();

	/**
		Update the player texture.
		*/
	void updateTexture();
#pragma endregion

#pragma region Player position, move state and velocity
	/**
		Holds the current state of the player.
		*/
	int moveState;

	/**
		Indicates if the player is in the air.
	*/
	bool inAir;

	/**
		The position of the player.
	*/
	int xPos, yPos;

	/**
		The velocity of the player.
	*/
	int xVel, yVel;

	/**
		Points to check for collision with player.
	*/
	SDL_Point collisionPoints[9];

	/**
		If player can jump, then y velocity is set to 200 and inAir = true.
	*/
	void accelerateY();
	
	/**
		Set x velocity to PLAYER_SPEED and current animation clip to 0.
	*/
	void accelerateX();
	/**
		Decreases the player's horizontal velocity by 1 and sets move state to stand still.
	*/
	void decelerateX();
	
	/**
		Reduces y velocity to -GRAVITY.
	*/
	void decelerateY();
	#pragma endregion
private:
	#pragma region Clips
	/**
		The clips for the running animation.
	*/
	SDL_Rect animationRunClips[10];
	/**
		The clip for the standing animation.
	*/
	SDL_Rect standClip;
	/**
		The clip for the jumping animation.
	*/
	SDL_Rect jumpClip;
	/**
		The internal clip counter for deciding what animation to use.
		Used to slow down the switching of clips for drawing.
	*/
	int internalClipCounter;

	/**
		Current running clip
	*/
	int currentRunClip;
	#pragma endregion
};
#endif
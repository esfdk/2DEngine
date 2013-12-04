#ifndef XMONSTER_H
#define XMONSTER_H
#include <SDL.h>
#include <SDL_image.h>

class xMonster{
public:
	xMonster();
	/**
		@param x x position of the monster.
		@param y y position of the monster.
	*/
	xMonster(int x, int y);
	/**
		The position of the monster.
	*/
	int xPos, yPos;

	/**
		Collision points for the monster.
	*/
	SDL_Point collisionPoints[9];

	/**
		The texture the monster is currently using.
	*/
	SDL_Texture *monsterTexture;

	/**
		The current clip of the animation to draw.
	*/
	SDL_Rect getCurrentClip();

	/**
		The size of the player texture.
	*/
	int textureHeight, textureWidth;

	/**
		Updates the texture of the monster.
	*/
	void updateTexture();
	/**
		True for right, false for left.
	*/
	bool direction;
private:
	/**
		The clips for the running animation.
	*/
	SDL_Rect animationRunClips[13];
	
	/**
		Clip counters to show the correct animation.
	*/
	int internalClipCounter, currentClip;
};
#endif
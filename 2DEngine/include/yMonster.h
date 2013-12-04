#ifndef YMONSTER_H
#define YMONSTER_H

#include <SDL.h>
#include <SDL_image.h>
class yMonster{
public:
	yMonster();
	/**
		@param x x position of the monster.
		@param y y position of the monster.
	*/
	yMonster(int x, int y);
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
		True if ymonster is going up, false if not.
	*/
	bool goingUp;
private:
	/**
		The clips for the flying animation.
	*/
	SDL_Rect animationRunClips[2];

	/**
	Clip counters to show the correct animation.
	*/
	int internalClipCounter, currentClip;
};
#endif
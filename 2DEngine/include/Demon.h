#ifndef DEMON_H
#define DEMON_H

#include "../include/Enemy.h"
#include <SDL.h>

class Demon : public Enemy{
public:
	/**
	* The path to the texture to use for the enemy.
	*/
	string texturePath = "Textures/Demon.png";

	/**
	* Specific settings for this enemy
	*/
	int textureHeight = 64, textureWidth = 79, animationClipAmount = 13, speed = 5;

	Demon();
	/**
		@param x x position of the enemy.
		@param y y position of the enemy.
	*/
	Demon(int x, int y);

	/**
	* Moves the enemy.
	* @param map The map to move the enemy on.
	*/
	virtual void move(Map map);

	/**
		Updates the texture of the enemy.
	*/
	virtual void updateTexture();
private:
	/**
	* The clips for the running animation.
	*/
	SDL_Rect animationClips[13];
	
	/**
		Clip counters to show the correct animation.
	*/
	int internalClipCounter, currentClip;
};
#endif
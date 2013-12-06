#ifndef COPTER_H
#define COPTER_H

#include "../include/Enemy.h"
#include <SDL.h>
#include <SDL_image.h>

class Copter : public Enemy{
public:
	Copter();
	/**
	@param x x position of the enemy.
	@param y y position of the enemy.
	*/
	Copter(int x, int y);

	/**
	* Moves the enemy.
	* @param map The map to move the enemy on.
	*/
	virtual void move(Map map);

	/**
	Updates the texture of the enemy.
	*/
	virtual void updateTexture();
};
#endif
#ifndef DEMON_H
#define DEMON_H

#include "../include/Enemy.h"
#include <SDL.h>

class Demon : public Enemy{
public:
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
};
#endif
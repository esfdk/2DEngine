#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include "../include/Map.h"
#include "../include/Window.h"
#include "../include/EngineSettings.h"

/**
* An enemy.
*/
class Enemy{
public:
	Enemy();
	~Enemy(){};

	/**
	* The path to the texture to use for the enemy.
	*/
	string texturePath = "";

	/**
	* True for right, false for left.
	*/
	bool direction;
	/**
	* The position of the enemy.
	*/
	int xPos, yPos;

	/**
	* Specific settings for this enemy type.
	*/
	int textureHeight, textureWidth, animationClipAmount, speed;

	/**
	* Game height and width of the enemy.
	*/
	int height, width;

	/**
	* Collision points for the enemy.
	*/
	SDL_Point collisionPoints[COLLISION_POINT_AMOUNT];

	/**
	* Base texture of the monster.
	*/
	SDL_Texture *texture;

	/**
	* Updates the texture of the enemy.
	*/
	virtual void updateTexture();

	/**
	* The current clip of the animation to draw.
	*/
	SDL_Rect getCurrentClip();

	/**
	* Moves the enemy.
	* @param map The map to move the enemy on.
	*/
	virtual void move(Map map);

protected:
	/**
	* The animation clips.
	*/
	SDL_Rect animationClips[4];

	/**
	* Clip counters to show the correct animation.
	*/
	int internalClipCounter, currentClip;

	/**
	* Checks collision points for collision
	*/
	bool Enemy::checkCollision(Map map);
};
#endif
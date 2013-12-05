#include "../include/Enemy.h"
#include "../include/Window.h"

Enemy::Enemy(){}


void Enemy::move(Map map)
{
	// Do not move default enemy.
}

void Enemy::updateTexture()
{
}

SDL_Rect Enemy::getCurrentClip()
{
	return animationClips[currentClip];
}

bool Enemy::checkCollision(Map map)
{
	for (int i = 0; i < 9; i++){
		SDL_Point tempPoint = collisionPoints[i];

		int tile = map.getTile(tempPoint.x, tempPoint.y);
		if (tile == TILE_SOLID)
		{
			return true;
		}
	}

	return false;
}
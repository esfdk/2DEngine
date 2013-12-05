#include "../include/Demon.h"
#include "../include/helperClass.h"

Demon::Demon(){}
Demon::Demon(int x, int y)
{
	xPos = x;
	yPos = y;
	texture = Window::LoadImage(texturePath);
	direction = false;

	printf("%d \n", textureWidth);

	currentClip = 0;

	// Creates the clips for the monster animation
	for (int i = 0; i < animationClipAmount; i++)
	{
		animationClips[i].x = i * textureWidth;
		animationClips[i].y = 0;
		animationClips[i].h = textureHeight;
		animationClips[i].w = textureWidth;
	}

	height = textureHeight - 2;
	width = textureWidth - 2;
}

void Demon::updateTexture()
{
	internalClipCounter = internalClipCounter % ((animationClipAmount * 2) - 2);
	currentClip = internalClipCounter / 2;

	internalClipCounter++;
}

void Demon::move(Map map)
{
	// Move right or left and turn around if walking into wall.
	for (int movement = 0; movement < speed; movement++)
	{
		if (direction)
		{ 
			// Going right
			HelperClass::getCollisionPoints(xPos + 1, yPos, width, height, collisionPoints);
			if (checkCollision(map))
			{
				direction = !direction;
				break;
			}
			xPos++;
		}
		else{ 
			// Going left
			HelperClass::getCollisionPoints(xPos - 1, yPos, width, height, collisionPoints);
			if (checkCollision(map))
			{
				direction = !direction;
				break;
			}
			xPos--;
		}
	}

	// Make monster fall
	for (int movement = 0; movement < GRAVITY; movement++)
	{
		HelperClass::getCollisionPoints(xPos, yPos + 1, width, height, collisionPoints);
		if (checkCollision(map)){
			break;
		}

		yPos++;
	}
}
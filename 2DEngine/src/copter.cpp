#include "../include/Copter.h"
#include "../include/helperClass.h"

Copter::Copter(){}
Copter::Copter(int x, int y){
	xPos = x;
	yPos = y;

	texture = Window::LoadImage(texturePath);
	direction = false;

	currentClip = 0;

	// Creates the clips for the monster animation
	for (int i = 0; i < animationClipAmount; i++)
	{
		animationRunClips[i].x = i * textureWidth;
		animationRunClips[i].y = 0;
		animationRunClips[i].h = textureHeight;
		animationRunClips[i].w = textureWidth;
	}

	height = textureHeight - 2;
	width = textureWidth - 4;
}
void Copter::updateTexture(){
	internalClipCounter = internalClipCounter % animationClipAmount;
	currentClip = internalClipCounter / 2;

	internalClipCounter++;
}

void Copter::move(Map map)
{
	// Move right or left and turn around if flying into wall.
	for (int movement = 0; movement < speed; movement++)
	{
		if (direction)
		{ 
			// Going up
			HelperClass::getCollisionPoints(xPos, yPos - 1, width, height, collisionPoints);
			if (checkCollision(map))
			{
				direction = !direction;
				break;
			}
			yPos--;
		}
		else{ 
			// Going down
			HelperClass::getCollisionPoints(xPos, yPos + 1, width, height, collisionPoints);
			if (checkCollision(map))
			{
				direction = !direction;
				break;
			}
			yPos++;
		}
	}
}
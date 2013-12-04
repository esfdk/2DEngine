#include "../include/yMonster.h"
#include "../include/window.h"
#include "../include/game.h"

yMonster::yMonster(){

}
/**
@param x x position of the monster.
@param y y position of the monster.
*/
yMonster::yMonster(int x, int y){
	xPos = x;
	yPos = y;

	monsterTexture = Window::LoadImage(Y_MONSTER_TEXTURE);
	goingUp = false;

	SDL_QueryTexture(monsterTexture, NULL, NULL, &textureWidth, &textureHeight);

	textureHeight = 64;
	textureWidth = textureWidth / 2;

	currentClip = 0;

	// Creates the clips for the monster animation
	for (int i = 0; i < 2; i++)
	{
		animationRunClips[i].x = i * textureWidth;
		animationRunClips[i].y = 0;
		animationRunClips[i].h = textureHeight;
		animationRunClips[i].w = textureWidth;
	}

	textureHeight -= 2;
	textureWidth -= 4;
}

/**
	Updates the texture of the monster.
*/
void yMonster::updateTexture(){
	internalClipCounter = internalClipCounter % 2;
	currentClip = internalClipCounter / 2;

	internalClipCounter++;
}

/**
The current clip of the animation to draw.
*/
SDL_Rect yMonster::getCurrentClip(){
	return animationRunClips[currentClip];
}
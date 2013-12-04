#include "../include/xMonster.h"
#include "../include/window.h"
#include "../include/game.h"

xMonster::xMonster(){

}
/**
	@param x x position of the monster.
	@param y y position of the monster.
*/
xMonster::xMonster(int x, int y){
	xPos = x;
	yPos = y;

	monsterTexture = Window::LoadImage(X_MONSTER_RUN_TEXTURE);
	direction = false;

	SDL_QueryTexture(monsterTexture, NULL, NULL, &textureWidth, &textureHeight);

	textureHeight = 64;
	textureWidth = textureWidth / 13;

	currentClip = 0;

	// Creates the clips for the monster animation
	for (int i = 0; i < 13; i++)
	{
		animationRunClips[i].x = i * textureWidth;
		animationRunClips[i].y = 0;
		animationRunClips[i].h = textureHeight;
		animationRunClips[i].w = textureWidth;
	}

	textureHeight -= 2;
	textureWidth -= 2;
}

/**
	Updates the texture of the monster.
*/
void xMonster::updateTexture(){
	internalClipCounter = internalClipCounter % 24;
	currentClip = internalClipCounter / 2;

	internalClipCounter++;
}

/**
	The current clip of the animation to draw.
*/
SDL_Rect xMonster::getCurrentClip(){
	return animationRunClips[currentClip];
}
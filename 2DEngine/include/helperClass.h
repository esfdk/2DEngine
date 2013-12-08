#ifndef HELPERCLASS_H
#define HELPERCLASS_H

#include <SDL.h>
#include "../include/window.h"
#include "../include/EngineSettings.h"
class HelperClass {
public:
	//Win/loss events
	static SDL_Event winEvent;
	static SDL_Event lossEvent;
	#define WIN_EVENT_CODE 1
	#define LOSS_EVENT_CODE 2

	// Move states
	#define STAND_RIGHT 0
	#define STAND_LEFT 1
	#define MOVE_LEFT 2
	#define MOVE_RIGHT 3

	// Amount of collision points for characters
	#define COLLISION_POINT_AMOUNT 9

	/**
	* Updates the array of collision points based on the arguments.
	*/
	static void getCollisionPoints(int newXPos, int newYPos, int textureWidth, int textureHeight, SDL_Point* collisionPoints);
	/**
	* Draws a loss screen when the player loses.
	*/
	static void drawWinScreen();
	/**
	* Draws a win screen when the player wins.
	*/
	static void drawLossScreen();
};
#endif
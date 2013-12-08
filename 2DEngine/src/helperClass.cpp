#include "../include/helperClass.h"

SDL_Event HelperClass::winEvent;
SDL_Event HelperClass::lossEvent;

void HelperClass::getCollisionPoints(int newXPos, int newYPos, int textureWidth, int textureHeight, SDL_Point* collisionPoints)
{
	// Calculate 9 collision points on the texture.
	for (int i = 0; i < 9; i++)
	{
		SDL_Point point;
		point.x = newXPos + ((i / 3) * (textureWidth / 2));
		point.y = newYPos + ((i % 3) * (textureHeight / 2));

		collisionPoints[i] = point;
	}
}


void HelperClass::drawWinScreen(){
	SDL_Color white = { 255, 255, 255 };
	SDL_Texture *msgGrats;
	SDL_Rect msgGratsBox;

	msgGrats = Window::RenderText(WIN_TEXT, "Textures/FreeSans.ttf", white, 50);

	SDL_QueryTexture(msgGrats, NULL, NULL, &msgGratsBox.w, &msgGratsBox.h);

	msgGratsBox.x = (Window::Box().w / 2) - (msgGratsBox.w / 2);
	msgGratsBox.y = (Window::Box().h / 2) - (msgGratsBox.h / 2) - 25;

	Window::Draw(msgGrats, msgGratsBox);
}

void HelperClass::drawLossScreen(){
	SDL_Color white = { 255, 255, 255 };
	SDL_Texture *msgGrats;
	SDL_Rect msgGratsBox;

	msgGrats = Window::RenderText(LOSS_TEXT, "Textures/FreeSans.ttf", white, 50);

	SDL_QueryTexture(msgGrats, NULL, NULL, &msgGratsBox.w, &msgGratsBox.h);

	msgGratsBox.x = (Window::Box().w / 2) - (msgGratsBox.w / 2);
	msgGratsBox.y = (Window::Box().h / 2) - (msgGratsBox.h / 2) - 25;

	Window::Draw(msgGrats, msgGratsBox);
}
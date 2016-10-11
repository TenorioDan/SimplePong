#pragma once
#include "GameObject.h"

class Ball : public GE161::GameObject
{
public:
	Ball(int ID, int width, int height, int deltax, int deltay, int startingX = 0, int startingY = 0);
	void update();
private:
	int framewidth, frameheight;
	int deltax, deltay;
};
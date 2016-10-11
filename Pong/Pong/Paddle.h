#pragma once
#include "GameObject.h"

class Paddle : public GE161::GameObject
{
public:
	Paddle(int ID, int width, int height, int startingX = 0, int startingY = 0);
	void update();
private:
	int framewidth, frameheight;
	int deltax, deltay;
};
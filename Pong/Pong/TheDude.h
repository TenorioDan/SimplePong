#pragma once
#include "GameObject.h"

class TheDude : public GE161::GameObject
{
public:
	TheDude(int ID, int width, int height, int startingX = 0, int startingY = 0);
	void update();
	bool getExcited();
	void setStartTime(int time);
private:
	int framewidth, frameheight;
	int deltax, deltay;
	int timetolive;
	int starttime;
	bool excited = false;
};
#include "Ball.h"
#include "Game.h"
#include "TheDude.h"

TheDude::TheDude(int ID, int width, int height, int startingX, int startingY)
:GameObject(ID, width, height, startingX, startingY)
{
	timetolive = 1500;
}

void TheDude::update()
{
	if (!excited)
		this->draw("normal");
	else{
		this->draw("excited");

		if (GE161::Game::theGame->getTicks() > starttime + timetolive)
			this->excited = false;
	}
}

void TheDude::setStartTime(int time)
{
	this->starttime = time;
	excited = true;
}

bool TheDude::getExcited()
{
	return this->excited;
}

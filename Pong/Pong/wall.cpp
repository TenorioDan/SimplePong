#include "Ball.h"
#include "Game.h"
#include "wall.h"

Wall::Wall(int ID, int width, int height, int startingX, int startingY)
:GameObject(ID, width, height, startingX, startingY)
{
	deltay = 2;
}

void Wall::update()
{
	this->moveY(deltay);
	this->draw("walling");

	if (this->getY() <= 0 || this->getY() >= GE161::Game::theGame->window()->clientHeight() - 40){
		deltay *= -1;
	}

}

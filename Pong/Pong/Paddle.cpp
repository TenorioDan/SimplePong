#include "Ball.h"
#include "Game.h"
#include "Paddle.h"

Paddle::Paddle(int ID, int width, int height, int startingX, int startingY)
:GameObject(ID, width, height, startingX, startingY)
{

}

void Paddle::update()
{
	this->draw("paddling");
}

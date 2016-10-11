#include "Ball.h"
#include "Game.h"
#include "Paddle.h"

Ball::Ball(int ID, int width, int height, int deltaX, int deltaY, int startingX, int startingY)
:GameObject(ID, width, height, startingX, startingY),
deltax(deltaX),
deltay(deltaY)
{

}

void Ball::update()
{
	this->moveX(deltax);
	this->moveY(deltay);
	this->draw("Rolling");

	if (this->getY() < 0){
		deltay = rand() % 3 + 1;
	}
	else if (this->getY() + this->height >= GE161::Game::theGame->window()->clientHeight()){
		deltay = -(rand() % 3 + 1);
	}

	if (this->getX() < 0){
		deltax = rand() % 3 + 1;
	}
	else if (this->getX() + this->width >= GE161::Game::theGame->window()->clientWidth()){
		deltax = -(rand() % 3 + 1);
	}


	for (int i = 0; i < GE161::Game::theGame->game_objects.size(); i++){
		GameObject* collision = GE161::Game::theGame->game_objects[i];

		if (this->overlapsWith(*collision)){

			if (collision->getID() == 3){
				deltax = -(rand() % 3 + 1);
				GE161::Game::theGame->SendEvent(1);
			}
			else if (collision->getID() == 4){
				deltax = (rand() % 3 + 1);
				GE161::Game::theGame->SendEvent(1);
			}
			else if (collision->getID() == 5){

				if (this->getX() < collision->getX()){
					deltax = -(rand() % 3 + 1);
				}
				else{
					deltax = (rand() % 3 + 1);
				}
			}
		}
	}
}

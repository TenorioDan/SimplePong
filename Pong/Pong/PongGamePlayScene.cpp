#include "PongGamePlayScene.h"

#include <stdlib.h>		// srand, rand
#include <time.h>		// time
#include "Ball.h"
#include "Paddle.h"
//PongGamePlayScene.cpp

PongGamePlayScene::PongGamePlayScene(Pong* pong) :
theGame(pong)
{

}

PongGamePlayScene::~PongGamePlayScene()
{
	delete ball;
	delete left_paddle;
	delete right_paddle;
	delete event_queue;
}

bool PongGamePlayScene::setup()
{
	GE161::Game::registerAsListener(GE161::Event::KEY_DOWN, this);
	GE161::Game::registerAsListener(GE161::Event::HIT_EVENT, this);
	// Rolling ball sprite sheet is from http://www.java-gaming.org/index.php?topic=21935.0.
	// It has 32 64x64 frames.
	texty1 = new GE161::Texty(GE161::Game::theGame->getRenderer(), GE161::Game::basePath() + "sample.ttf", 18, true);

	int sprite_count = 1;
	// Start the ball with its upper left in the middle of the window
	ball = new Ball(++sprite_count, frameWidth_, frameHeight_, 1, 1, theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2);
	GE161::Sprite* ballSpriteSheet = new GE161::Sprite(frameWidth_, frameHeight_);

	int ball_rows = 4;
	int ball_columns = 8;

	for (int row = 0; row < ball_rows; row++)
	{
		for (int column = 0; column < ball_columns; column++)
		{
			int f = ballSpriteSheet->makeFrame(
				GE161::Game::basePath() + "RollingBall.png",
				column*frameWidth_, row*frameHeight_);
			ballSpriteSheet->addFrameToSequence("Rolling", f);
		}
	}
	ball->attachSprite(ballSpriteSheet);

	//left_paddle = new GE161::GameObject(20, theGame->window()->clientHeight() / 2);
	paddle_frame_width = 20;
	paddle_frame_height = 100;

	right_paddle = new Paddle(++sprite_count, paddle_frame_width, paddle_frame_height, theGame->window()->clientWidth() - paddle_x_offset, theGame->window()->clientHeight() / 2);
	GE161::Sprite* paddle_sprite_sheet = new GE161::Sprite(paddle_frame_width, paddle_frame_height);
	int p = paddle_sprite_sheet->makeFrame(GE161::Game::basePath() + "paddle.png", 0, 0);
	paddle_sprite_sheet->addFrameToSequence("paddling", p);
	right_paddle->attachSprite(paddle_sprite_sheet);

	left_paddle = new Paddle(++sprite_count, paddle_frame_width, paddle_frame_height, paddle_x_offset, theGame->window()->clientHeight() / 2);
	left_paddle->attachSprite(paddle_sprite_sheet);

	theGame->game_objects.push_back(ball);
	theGame->game_objects.push_back(right_paddle);
	theGame->game_objects.push_back(left_paddle);

	// seed the random number generator with the current time
	srand(static_cast<unsigned int>(time(NULL)));
	return true;
}

int PongGamePlayScene::draw()
{
	texty1->write("Score " + std::to_string(score), score_pos_x, score_pos_y);
	theGame->update_world();

	if (bounceCount_ <= max_bounce)
	{
		return GE161::Game::CONTINUE_SCENE;
	}
	else     // bounced out
	{
		return -1;  // stop game
	}
}


void PongGamePlayScene::onEvent(GE161::Event& event)
{
	if (event.type == GE161::Event::KEY_DOWN)  // this test isn't necessary
	{
		if (event.key == "UP"){
			right_paddle->moveY(-paddle_movement);

			if (right_paddle->getY() <= 0){
				right_paddle->setPos(right_paddle->getX(), 0);
			}
			
		}
		else if (event.key == "DOWN"){
			right_paddle->moveY(paddle_movement);

			if (right_paddle->getY() >= theGame->window()->clientHeight() - right_paddle_offset){
				right_paddle->setPos(right_paddle->getX(), theGame->window()->clientHeight() - right_paddle_offset);
			}
		}
		else if (event.key == "BACKSPACE"){
			ball->setPos(theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2);
		}
	}
}
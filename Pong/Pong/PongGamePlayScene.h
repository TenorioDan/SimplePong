//PongGamePlayScene.h

#pragma once

#include "Pong.h"
#include "Scene.h"
#include "GameObject.h"
#include "Event.h"
#include "Texty.h"
#include "Ball.h"
#include "Paddle.h"

class PongGamePlayScene : public GE161::Scene
{
public:
	PongGamePlayScene(Pong* theGame);
	~PongGamePlayScene();
	bool setup();
	int draw();

private:
	Pong* theGame;
	GE161::Texty* texty1;
	void onEvent(GE161::Event& ev);
	GE161::EventQueue* event_queue;
	Ball* ball;
	Paddle* left_paddle;
	Paddle* right_paddle;

	int frameWidth_ = 64;
	int frameHeight_ = 64;
	int paddle_frame_width;
	int paddle_frame_height;
	int right_paddle_offset = 100;
	int paddle_x_offset = 40;
	int paddle_movement = 5;
	int bounceCount_ = 0;
	int max_bounce = 8;
	int score_pos_x = 250;
	int score_pos_y = 50;
	int font_size = 18;
	unsigned int score = 0;
	bool drawPow = false;

};


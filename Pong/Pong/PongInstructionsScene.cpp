// PongInstructionScene.cpp

#include "PongInstructionsScene.h"
#include <iostream>


PongInstructionsScene::PongInstructionsScene(Pong* game) :
theGame(game)
{
}

PongInstructionsScene::~PongInstructionsScene()
{
	delete instructions;
}


bool PongInstructionsScene::setup()
{
	//instructions = new GE161::GameObject(20, 20);
	//GE161::Sprite* instructionsImage = new GE161::Sprite(450, 300);
	//frameIndex = instructionsImage->makeFrame(GE161::Game::basePath() + "Instructions.png", 0, 0);
	//instructions->attachSprite(instructionsImage);
	texty1 = new GE161::Texty(GE161::Game::theGame->getRenderer(), GE161::Game::basePath() + "sample.ttf", 18, true);


	playGameRequested = false;
	exitRequested = false;

	//set framerate
	GE161::Game::theGame->framerate = 30;

	GE161::Game::registerAsListener(GE161::Event::KEY_DOWN, this);
	
	GE161::Game::debugOut("PongInstructionsScene::setup completed!");
	return true;
}

int PongInstructionsScene::draw()
{
	//instructions->draw(frameIndex);
	texty1->write("INSTRUCTIONS", theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2);
	texty1->write("Hit the ball for points!", theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2 - 40);
	texty1->write("Press space to start.", theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2 + 30);
	texty1->write("Press X to quit.", theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2 + 20);

	if (playGameRequested)
	{
		return 1;		// don't call draw again, go on to next scene
	}
	else if (exitRequested)
	{
		return -1;		// stop program
	}

	return GE161::Game::CONTINUE_SCENE;
}

void PongInstructionsScene::onEvent(GE161::Event& event)
{
	if (event.type == GE161::Event::KEY_DOWN)  // this test isn't necessary
	{
		if (event.key == " ")
			playGameRequested = true;
		else if (event.key == "X")
			exitRequested = true;
	}
}

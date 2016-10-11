#include "Game.h"
#include <iostream>

void GE161::Game::main(int x)
{
	if (x != 8675309)
	{
		fatalSDLError("Do not invoke GE161::Game::main()");
		return;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fatalSDLError("SDL_Init(SDL_INIT_EVERYTHING) Error in main(): ", SDL_GetError());
		return;
	}

	// Invoke the game's overridden setup() method, and create the SDL window.
	window_ = new GE161::Window();
	setup();
	window_->initialize();
	window_->clearBackground();

	eventQueue_ = new GE161::EventQueue();

	std::string sceneName = GE161::Game::START_GAME;
	int returnCode = CONTINUE_SCENE;

	// Loop through the outer while loop once per scene.
	// A negative return code from a scene says "Stop the program!"
	while (returnCode >= 0)
	{
		// Ask the game which scene to do next.
		sceneName = GE161::Game::theGame->chooseScene(sceneName, returnCode);
		GE161::Scene* scene = GE161::Game::theGame->lookUpScene(sceneName);

		// Now we have the scene to use.  First, run its setup().
		bool success = scene->setup();
		if (!success)
		{
			fatalSDLError("error in main(), setup failed for scene", sceneName);
			return;
		}

		// setup() succeeded.  Run its draw() until a non-zero return code.
		returnCode = CONTINUE_SCENE;
		// Loop through the inner while loop once per frame in scene.
		while (returnCode == CONTINUE_SCENE)
		{
			currentTime = theGame->getTicks();

			if (currentTime >= lastTime + 5000){
				lastTime = currentTime;
				debugOut(std::to_string(total_frames/5));
				total_frames = 0;
			}

			eventQueue_->getSDLEvents();
			eventQueue_->callEventListeners();

			window_->clearBackground();
			returnCode = scene->draw();
			window_->drawToScreen();

			theGame->delay(1000 / framerate);
			total_frames++;
		}
		std::string m = std::string("return code from ") + sceneName + std::string(": ") + std::to_string(returnCode);
		debugOut(m);
	}

	SDL_Quit();
	return;
}
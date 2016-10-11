// PongInstructionsScene.h

#pragma once

#include "Pong.h"
#include "GameObject.h"
#include "Event.h"
#include "Texty.h"

class PongInstructionsScene : public GE161::Scene
{
public:
	PongInstructionsScene(Pong* theGame);
	~PongInstructionsScene();

	// Override Scene methods.
	bool setup();
	int draw();

	// Override EventListener method.
	void onEvent(GE161::Event& ev);

private:
	Pong* theGame;
	GE161::Texty* texty1;
	GE161::GameObject* instructions;
	int frameIndex;
	bool playGameRequested;
	bool exitRequested;
};


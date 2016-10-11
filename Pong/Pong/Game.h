#pragma once

#include <string>
#include <map>
#include "Window.h"
#include "Scene.h"
#include "EventQueue.h"
#include "GameObject.h"

namespace GE161
{
	class Game
	{
		friend class Sprite;
		friend class GameObject;

	public:
		Game();
		~Game();

		// These functions are called by the game code.
		void setWindowColor(int r, int g, int b);
		void addScene(std::string name, Scene* scene);
		SDL_Renderer* getRenderer();
		Scene* lookUpScene(std::string name);
		Window* window();
		static void registerAsListener(int eventType, EventListener* listener);
		static void SendEvent(int eventType);

		// Helpful functions exposed to the game programmer.
		static void delay(int milliseconds);
		static std::string pathSlash();
		static std::string basePath();
		static void debugOut(std::string);
		static int getTicks();

		// These functions have to be overridden by the game code.
		virtual void setup() = 0;
		virtual std::string chooseScene(std::string prevScene, int prevReturnCode) = 0;

		// This function should be called exactly once by main().
		void main(int x);
		void update_world();

		static const std::string START_GAME;
		static const std::string EXIT_GAME;

		static Game* theGame;
		static const int CONTINUE_SCENE = 0;

		int framerate = 30;
		std::vector<GameObject*> game_objects;

	private:
		
		unsigned int lastTime = 0, currentTime = 0, total_frames = 0;

		Window* window_;
		std::map<std::string, Scene*> sceneMap;
		EventQueue* eventQueue_;
	};

}

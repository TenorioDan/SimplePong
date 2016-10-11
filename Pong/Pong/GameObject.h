#pragma once

#include <string>
#include "Sprite.h"

namespace GE161
{
	class GameObject
	{
		friend class Game;
	public:
		GameObject(int ID, int width, int height, int startingX, int startingY);
		~GameObject();

		void setPos(int x, int y);
		void moveX(int delta);
		void moveY(int delta);
		int getX();
		int getY();
		int getID();
		void attachSprite(Sprite* sprite);
		void draw(int frameIndex);
		void draw(std::string sequenceName);
		virtual void update() = 0;
		bool overlapsWith(GameObject& otherGameObject);	
	protected:
		int ID;
		int x_;		// current position of
		int y_;		// this game object
		int width;
		int height;
		Sprite* sprite_;

	};

}


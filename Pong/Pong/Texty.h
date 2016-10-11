// Texty.h

#pragma once

#include <iostream>
#include <SDL.h>
#include "SDL_ttf.h"
namespace GE161
{
	class Texty
	{

	public:
		Texty(SDL_Renderer* renderer, std::string fontName, int fontSize = 10, bool visible = true);
		~Texty();

		enum writeOption_t { CONTINUE, NEXT_LINE };

		void write(std::string text, writeOption_t option = Texty::CONTINUE);

		void write(std::string text, int x, int y);


	private:
		SDL_Renderer *renderer;
		std::string text;
		std::string fontName;
		int fontSize;
		bool visible;
		int currX, currY, initX, initY;
	};
}
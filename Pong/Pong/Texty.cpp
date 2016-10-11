// Texty.cpp

#include "Texty.h"   // You can add or remove #include files as needed.
#include <iostream>
#include <sstream>
#include "Windows.h"
#include "ErrorLogger.h"

/**
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param dst The destination rectangle to render the texture to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst,
	SDL_Rect *clip = nullptr)
{
	SDL_RenderCopy(ren, tex, clip, &dst);
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height and taking a clip of the texture if desired
* If a clip is passed, the clip's width and height will be used instead of
*	the texture's
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,
	SDL_Rect *clip = nullptr)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr){
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}
	renderTexture(tex, ren, dst, clip);
}

SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
	SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
	//Open the font
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr){
		logSDLError(std::cout, "TTF_OpenFont");
		return nullptr;
	}
	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surf == nullptr){
		TTF_CloseFont(font);
		logSDLError(std::cout, "TTF_RenderText");
		return nullptr;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr){
		logSDLError(std::cout, "CreateTexture");
	}
	//Clean up the surface and font
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}

GE161::Texty::Texty(SDL_Renderer *renderer, std::string fontName, int fontSize, bool visible)
:renderer{ renderer }, fontName{ fontName }, fontSize{ fontSize }, visible{visible}
{
	this->currX = 0;
	this->currY = 0;

	if (TTF_Init() != 0){
		logSDLError(std::cout, "TTF_Init");
		SDL_Quit();
		//return 1;
	};
}

void GE161::Texty::write(std::string text, writeOption_t option)
{
	bool found_newline = false;
	std::string::size_type i = text.find("\n");

	if (i != std::string::npos) {
		found_newline = true;
		text.erase(i, 2);
	}

	if (text == "")
		text = " ";

	SDL_Color color = { 0, 0, 0, 255 };
	SDL_Texture *texture = renderText(text, fontName, color, fontSize, renderer);
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	int x = currX;
	int y = currY;
	renderTexture(texture, renderer, currX, currY);

	if (found_newline) {
		currY += h;
		currX = initX;
	}
	else
	{
		currX += w;
	}

}

void GE161::Texty::write(std::string text, int x, int y)
{
	bool found_newline = false;
	std::string::size_type i = text.find("\n");

	if (i != std::string::npos) {
		found_newline = true;
		text.erase(i, 2);
	}

	initX = x;
	initY = y;
	currX = x;
	currY = y;
	SDL_Color color = { 0, 0, 0, 255 };
	SDL_Texture *texture = renderText(text, fontName, color, fontSize, renderer);
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	
	currX += w;

	if (found_newline) {
		currY += h;
		currX = initX;
	}
	renderTexture(texture, renderer, x, y);
}

GE161::Texty::~Texty()
{

}

#include "GameObject.h"
#include "Game.h"


GE161::GameObject::GameObject(int ID, int width, int height, int startingX, int startingY) :
ID(ID),
width(width),
height(height),
x_(startingX),
y_(startingY),
sprite_(nullptr)
{
}


GE161::GameObject::~GameObject()
{
}

int GE161::GameObject::getID(){
	return this->ID;
}

void GE161::GameObject::setPos(int x, int y)
{
	x_ = x;
	y_ = y;
}

void GE161::GameObject::moveX(int delta)
{
	x_ += delta;
}

void GE161::GameObject::moveY(int delta)
{
	y_ += delta;
}

int GE161::GameObject::getX()
{
	return x_;
}

int GE161::GameObject::getY()
{
	return y_;
}

void GE161::GameObject::attachSprite(GE161::Sprite* sprite)
{
	sprite_ = sprite;	
}
void GE161::GameObject::draw(int frameIndex)
{
	if (sprite_ == nullptr)
	{
		debugOut("GameObject::draw called, but no Sprite is attached.");
		return;
	}

	SDL_Rect srcrect = {sprite_->frames[frameIndex].x, sprite_->frames[frameIndex].y, sprite_->frameWidth_, sprite_->frameHeight_};
	SDL_Rect destrect = {x_, y_, sprite_->frameWidth_, sprite_->frameHeight_};
	int success = SDL_RenderCopy(GE161::Game::theGame->getRenderer(), sprite_->frames[frameIndex].texture, &srcrect, &destrect);
	if (success != 0)
	{
		fatalSDLError("In GameObject::draw, SDL_RenderCopy: ", SDL_GetError());
	}
}

void GE161::GameObject::draw(std::string sequenceName)
{
	draw(sprite_->getNextFrameIndex(sequenceName));
}

bool GE161::GameObject::overlapsWith(GameObject& gameObject){
	if (x_ < gameObject.getX() + gameObject.sprite_->frameWidth_
		&& x_ + sprite_->frameWidth_ > gameObject.getX()
		&& y_ < gameObject.getY() + gameObject.sprite_->frameHeight_
		&& y_ + sprite_->frameHeight_ > gameObject.getY())
	{
		return true;
	}
	return false;

}



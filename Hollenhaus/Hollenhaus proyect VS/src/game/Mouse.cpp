#include "pch.h"
#include "Mouse.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

constexpr uint8_t MOUSE_SIZE = 40,
					PADDING = 20;

Mouse::Mouse(const std::string& image, int frames) : image_(&sdlutils().images().at(image))
{
	frameWidth_ = image_->width()/frames;

	srcRect_ = {
		0,0,
		frameWidth_,
		image_->height()
	};
	destRect_ = {
		0,0,
		MOUSE_SIZE,
		MOUSE_SIZE
	};

	sdlutils().hideCursor();

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { changeFrame(1); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { changeFrame(0); });
}

Mouse::~Mouse()
{
	
}

void Mouse::render() const
{
	image_->render(srcRect_, destRect_);
}

void Mouse::update()
{
	SDL_GetMouseState(&destRect_.x, &destRect_.y);
	destRect_.x -= PADDING;
	destRect_.y -= PADDING;
}

void Mouse::changeFrame(int frame)
{
	srcRect_.x = frameWidth_ * frame;
}
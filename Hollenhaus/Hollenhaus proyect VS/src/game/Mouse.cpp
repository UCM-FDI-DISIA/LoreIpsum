#include "Mouse.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
Mouse::Mouse(const std::string& image) : image_(&sdlutils().images().at(image))
{
	srcRect_ = {
		0,0,
		image_->width()/2,
		image_->height()/2
	};
	destRect_ = {
		0,0,
		image_->width()/2,
		image_->height()/2
	};
	sdlutils().hideCursor();
}

Mouse::~Mouse()
{
	delete image_;
}

void Mouse::render() const
{
	image_->render(destRect_);
}

void Mouse::update()
{
	SDL_GetMouseState(&destRect_.x, &destRect_.y);
}

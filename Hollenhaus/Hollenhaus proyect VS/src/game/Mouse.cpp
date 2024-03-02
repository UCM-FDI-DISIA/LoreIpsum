#include "Mouse.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
Mouse::Mouse(const std::string& image) : image_(&sdlutils().images().at(image))
{
	rect_ = {
		0,0,
		image_->width(),
		image_->height()
	};
	SDL_ShowCursor(false);
}

Mouse::~Mouse()
{
	delete image_;
}

void Mouse::render() const
{
	image_->render(rect_);
}

void Mouse::update()
{
	SDL_GetMouseState(&rect_.x, &rect_.y);
}

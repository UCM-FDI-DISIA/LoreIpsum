#include "../pchs/pch.h"
#include "Fade.h"

Fade::Fade(int opacity) : image_(&sdlutils().images().at("black_box")), opacity_(opacity)
{
}

void Fade::render() const
{
	image_->render(rect_, opacity_);
}

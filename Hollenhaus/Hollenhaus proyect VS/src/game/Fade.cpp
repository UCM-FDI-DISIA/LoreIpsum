#include "..\pchs\pch.h"
#include "Fade.h"

Fade::Fade(int opacity) : opacity_(opacity), image_(&sdlutils().images().at("black_box"))
{
}

void Fade::render() const
{
	image_->render(rect_, opacity_);
}

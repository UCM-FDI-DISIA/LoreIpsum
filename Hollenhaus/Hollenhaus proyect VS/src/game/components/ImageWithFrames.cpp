#include <../pchs/pch.h>
#include "ImageWithFrames.h"
#include "../../sdlutils/SDLUtils.h"

ImageWithFrames::ImageWithFrames(int rows, int cols, int speed)
: currentRow_(0), currentCol_(0), nRows_(rows), nCols_(cols), frameSpeed(speed)
{
}

ImageWithFrames::ImageWithFrames(SpriteRenderer* img, int rows, int cols, int speed) :
	spriteRend_(img),
	currentRow_(0),
	currentCol_(0),
	nRows_(rows),
	nCols_(cols),
	frameSpeed(speed)
{
}

ImageWithFrames::~ImageWithFrames()
{
}

void ImageWithFrames::initComponent()
{
	spriteRend_ = mngr_->getComponent<SpriteRenderer>(ent_);
	spriteRend_->setAnimated(true);
	image_ = spriteRend_->getTexture();

	frameWidth_ = image_->width() / nCols_;
	frameHeight_ = image_->height() / nRows_;
	frameTimer = sdlutils().currRealTime();

	spriteRend_->setRows(nRows_);
	spriteRend_->setCols(nCols_);

	syncRenderer();
}

void ImageWithFrames::update()
{
	if (sdlutils().currRealTime() > frameTimer + frameSpeed)
	{
		frameTimer = sdlutils().currRealTime();
		/*auto col = nCols_;
		if (col > 1) col -= 1;

		auto row = nRows_;
		if (row > 1) row -= 1;

		currentCol_ = (currentCol_ + 1) % col;
		currentRow_ = (currentRow_ + 1) % row;*/

		currentCol_ = (currentCol_ + 1) % (nCols_ - 0);
		if (currentCol_ == 0 && nRows_ > 1)
			currentRow_ = (currentRow_ + 1) % (nRows_ - 0);
	}
	syncRenderer();
}

void ImageWithFrames::syncRenderer()
{
	auto frame = Vector2D(currentCol_ * frameWidth_, currentRow_ * frameHeight_);
	const SDL_Rect srce = build_sdlrect(
		frame,
		frameWidth_,
		frameHeight_
	);
	spriteRend_->setSourceRect(srce);
}

#include <../pchs/pch.h>
#include "ImageWithFrames.h"
#include "../../sdlutils/SDLUtils.h"
constexpr int FRAME_SPEED = 300	;

ImageWithFrames::ImageWithFrames(int rows, int cols) : currentRow_(0), currentCol_(0),
                                                       nRows_(rows), nCols_(cols)
{
}

ImageWithFrames::ImageWithFrames(SpriteRenderer* img, int rows, int cols) :
	spriteRend_(img),
	currentRow_(0),
	currentCol_(0),
	nRows_(rows),
	nCols_(cols)
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
	if (sdlutils().currRealTime() > frameTimer + FRAME_SPEED)
	{
		/*auto col = nCols_;
		if (col > 1) col -= 1;

		auto row = nRows_;
		if (row > 1) row -= 1;

		currentCol_ = (currentCol_ + 1) % col;
		currentRow_ = (currentRow_ + 1) % row;*/

		currentCol_ = (currentCol_ + 1) % nCols_;
		if (currentCol_ == 0)
			currentRow_ = (currentRow_ + 1) % nRows_;

		frameTimer = sdlutils().currRealTime();
		syncRenderer();
	}
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

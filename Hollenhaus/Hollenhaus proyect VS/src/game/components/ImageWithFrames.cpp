#include <../pchs/pch.h>
#include "ImageWithFrames.h"
#include "../../sdlutils/SDLUtils.h"

ImageWithFrames::ImageWithFrames(int rows, int cols, int lups, int speed)
	: currentRow_(0), currentCol_(0), nRows_(rows), nCols_(cols), frameSpeed(speed), loops(lups), callbacksExecuted(false)
{
}

ImageWithFrames::ImageWithFrames(SpriteRenderer* img, int rows, int cols, int lups, int speed) :
	spriteRend_(img),
	currentRow_(0),
	currentCol_(0),
	nRows_(rows),
	nCols_(cols),
	frameSpeed(speed),
	loops(lups),
	callbacksExecuted(false)
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
	if (sdlutils().currRealTime() > frameTimer + frameSpeed && (loops > 0 || loops == -1))
	{
		frameTimer = sdlutils().currRealTime();

		currentCol_ = (currentCol_ + 1) % (nCols_ - 0);
		if (currentCol_ == 0 && nRows_ > 1)
			currentRow_ = (currentRow_ + 1) % (nRows_ - 0);

		// 
		if (loops != -1 && ((currentCol_ + 1) * (currentRow_ + 1) >= nCols_ * nRows_))
			loops--;
	}
	syncRenderer();

	// Si ha terminado todas los loops que debe hacer ejecuta el callback
	if (loops <= 0 && loops != -1 && !callbacksExecuted) {
		useCallback();
		callbacksExecuted = true;
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

void ImageWithFrames::setSprite(std::string newSprite, int rows, int cols, int loop)
{
	spriteRend_->setTexture(newSprite);
	currentRow_ = 0;
	currentRow_= 0;
	nRows_ = rows;
	nCols_ = cols;
	loops = loop;
	spriteRend_->setAnimated(true);
	image_ = spriteRend_->getTexture();

	frameWidth_ = image_->width() / nCols_;
	frameHeight_ = image_->height() / nRows_;
	frameTimer = sdlutils().currRealTime();

	spriteRend_->setRows(nRows_);
	spriteRend_->setCols(nCols_);

	//syncRenderer();
}

void ImageWithFrames::addCallback(SDLEventCallback _callback)
{
	callbacks.push_back(_callback);
}

void ImageWithFrames::useCallback() const
{
	for (auto e : callbacks) {
		e();
	}
}
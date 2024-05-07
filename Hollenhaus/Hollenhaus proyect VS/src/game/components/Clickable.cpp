#include "../pchs/pch.h"
#include "Clickable.h"


Clickable::~Clickable()
{
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { onClickDown(); });
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { onClickUp(); });
}

void Clickable::onClickDown()
{
	if (boxCol_->isCursorOver())
	{
		isClicked = true;
		spriteRend_->setTexture(lastFrame);
	}
}

void Clickable::onClickUp()
{
	if (isClicked)
	{
		isClicked = false;
		spriteRend_->setTexture(firstFrame);
	}
}

void Clickable::initComponent()
{
	spriteRend_ = mngr_->getComponent<SpriteRenderer>(ent_);
	boxCol_ = mngr_->getComponent<BoxCollider>(ent_);

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { onClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { onClickUp(); });
}

void Clickable::update()
{
	if (hoverFrame.empty()) return;

	if (!isClicked)
	{
		if (boxCol_->isCursorOver())
		{
			if (spriteRend_->getTexture() != &sdlutils().images().at(hoverFrame))
				spriteRend_->setTexture(hoverFrame);
		}
		else
		{
			if (spriteRend_->getTexture() != &sdlutils().images().at(firstFrame))
				spriteRend_->setTexture(firstFrame);
		}
	}
	else if (spriteRend_->getTexture() != &sdlutils().images().at(lastFrame))
		spriteRend_->setTexture(lastFrame);
}

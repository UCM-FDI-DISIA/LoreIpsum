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
		spriteRend_->setTexture(clickedFrame);
	}
}

void Clickable::onClickUp()
{
	if (isClicked)
	{
		isClicked = false;
		spriteRend_->setTexture(originalFrame);
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
			if (spriteRend_->getTexture() != &sdlutils().images().at(originalFrame))
				spriteRend_->setTexture(originalFrame);
		}
	}
	else if (spriteRend_->getTexture() != &sdlutils().images().at(clickedFrame))
		spriteRend_->setTexture(clickedFrame);
}

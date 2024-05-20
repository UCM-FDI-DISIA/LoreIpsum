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
		if (imageMode)
			spriteRend_->setTexture(clickedFrame);
	}
}

void Clickable::onClickUp()
{
	if (isClicked)
	{
		isClicked = false;
		if (imageMode)
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
	if (imageMode && hoverFrame.empty()) return;

	if (!isClicked)
	{
		if (boxCol_->isCursorOver())
		{
			if (imageMode)
			{
				if (spriteRend_->getTexture() != &sdlutils().images().at(hoverFrame))
					spriteRend_->setTexture(hoverFrame);
			}
			else
			{
				spriteRend_->setMultiplyColor(hoverColor);
			}
		}
		else
		{
			if (imageMode)
			{
				if (spriteRend_->getTexture() != &sdlutils().images().at(originalFrame))
					spriteRend_->setTexture(originalFrame);
			}
			else
			{
				spriteRend_->setMultiplyColor(originalColor);
			}
		}
	}
	else if (imageMode && spriteRend_->getTexture() != &sdlutils().images().at(clickedFrame))
	{
		if (imageMode)
		{
			spriteRend_->setMultiplyColor(clickedColor);
		}
		else
		{
			spriteRend_->setTexture(clickedFrame);
		}
	}

}

#include "..\pchs\pch.h"
#include "ClickableText.h"


ClickableText::~ClickableText()
{
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { onClickDown(); });
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { onClickUp(); });
}

void ClickableText::onClickDown()
{
	if (boxCol_->isCursorOver()) 
	{
		isClicked = true;
		spriteRend_->setTexture(lastFrame);
	}
}

void ClickableText::onClickUp()
{
	if (isClicked)
	{
		isClicked = false;
		spriteRend_->setTexture(firstFrame);
	}
}

void ClickableText::initComponent()
{
	spriteRend_ = mngr_->getComponent<SpriteRenderer>(ent_);
	boxCol_ = mngr_->getComponent<BoxCollider>(ent_);

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { onClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { onClickUp(); });
}


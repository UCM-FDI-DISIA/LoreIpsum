#include "../pchs/pch.h"
#include "ClickableText.h"

#include "basics/TextComponent.h"


ClickableText::~ClickableText()
{
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { onClickDown(); });
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { onClickUp(); });
}

void ClickableText::onClickDown()
{
	if (clickedColor.a == 0) return;
	if (boxCol_->isCursorOver())
	{
		isClicked = true;
		textComp_->setColor(clickedColor);
	}
}

void ClickableText::onClickUp()
{
	if (originalColor.a == 0) return;
	if (isClicked)
	{
		isClicked = false;
		textComp_->setColor(originalColor);
	}
}

void ClickableText::initComponent()
{
	textComp_ = mngr_->getComponent<TextComponent>(ent_);
	boxCol_ = mngr_->getComponent<BoxCollider>(ent_);

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { onClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { onClickUp(); });
}

void ClickableText::update()
{
	if (hoverColor.a == 0) return;

	if (!isClicked)
	{
		if (boxCol_->isCursorOver())
		{
			if (!compareColors(textComp_->getColor(), hoverColor))
				textComp_->setColor(hoverColor);
		}
		else
		{
			if (!compareColors(textComp_->getColor(), originalColor))
				textComp_->setColor(originalColor);
		}
	}
	else if (!compareColors(textComp_->getColor(), clickedColor))
		textComp_->setColor(clickedColor);
}


/// devuelve true si son iguales
bool ClickableText::compareColors(SDL_Color first, SDL_Color last)
{
	if (first.a != last.a) return false;
	if (first.r != last.r) return false;
	if (first.g != last.g) return false;
	if (first.b != last.b) return false;
	return true;
}

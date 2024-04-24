#include <../pchs/pch.h>
#include "InputForTextWritter.h"
#include "../components/TextWritter.h"
#include "../../sdlutils/InputHandler.h"

InputForTextWritter::InputForTextWritter()
{
}

InputForTextWritter::~InputForTextWritter()
{
}

void InputForTextWritter::initComponent()
{
	tw = ent_->getComponent<TextWritter>();
}

void InputForTextWritter::update()
{
	if (ih().keyDownEvent())
	{
		if (ih().isKeyDown(SDLK_0))
		{
			tw->UpdateText("0");
		}
		if (ih().isKeyDown(SDLK_1))
		{
			tw->UpdateText("1");
		}
		if (ih().isKeyDown(SDLK_2))
		{
			tw->UpdateText("2");
		}
		if (ih().isKeyDown(SDLK_3))
		{
			tw->UpdateText("3");
		}
		if (ih().isKeyDown(SDLK_4))
		{
			tw->UpdateText("4");
		}
		if (ih().isKeyDown(SDLK_5))
		{
			tw->UpdateText("5");
		}
		if (ih().isKeyDown(SDLK_6))
		{
			tw->UpdateText("6");
		}
		if (ih().isKeyDown(SDLK_7))
		{
			tw->UpdateText("7");
		}
		if (ih().isKeyDown(SDLK_8))
		{
			tw->UpdateText("8");
		}
		if (ih().isKeyDown(SDLK_9))
		{
			tw->UpdateText("9");
		}
		if (ih().isKeyDown(SDLK_PERIOD))
		{
			tw->UpdateText(".");
		}
		if (ih().isKeyDown(SDLK_BACKSPACE))
		{
			tw->DeleteLastChar();
		}
		if (ih().isKeyDown(SDLK_RETURN) || ih().isKeyDown(SDLK_RETURN2))
		{
			tw->DeleteLastChar();
		}
	}
}

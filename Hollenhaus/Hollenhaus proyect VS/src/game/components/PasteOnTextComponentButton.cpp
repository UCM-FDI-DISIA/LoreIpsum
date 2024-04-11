#include "pch.h"
#include "PasteOnTextComponentButton.h"
#include "basics/TextComponent.h"
#include "basics/BoxCollider.h"
#include <windows.h>

PasteOnTextComponentButton::PasteOnTextComponentButton()
{
}

PasteOnTextComponentButton::~PasteOnTextComponentButton()
{
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { clickButton(); });
}

void PasteOnTextComponentButton::initComponent()
{
	tc = ent_->getComponent<TextComponent>();
	bc = ent_->getComponent<BoxCollider>();
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { clickButton(); });
}

void PasteOnTextComponentButton::update()
{
}

void PasteOnTextComponentButton::clickButton()
{
	if (bc->isCursorOver()) {
		// Se pega el contenido del clipboard en el TextComponent
		OpenClipboard(0);
		std::string myval = *(std::string*)GetClipboardData(CF_TEXT);
		CloseClipboard();

		tc->setTxt(myval);
	}
}

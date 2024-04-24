#include <../pchs/pch.h>
#include "PasteOnTextComponentButton.h"
#include "basics/TextComponent.h"
#include "basics/BoxCollider.h"
#include <windows.h>

// Este componente necesita un BoxCollider en su entidad para actuar de botón
// Además, debe recibir un textComponent (normalmente de otra entidad) para modificarlo al activar el botón
PasteOnTextComponentButton::PasteOnTextComponentButton(TextComponent* textComponent)
{
	tc = textComponent;
}

PasteOnTextComponentButton::~PasteOnTextComponentButton()
{
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { clickButton(); });
}

void PasteOnTextComponentButton::initComponent()
{
	bc = ent_->getComponent<BoxCollider>();
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { clickButton(); });
}

void PasteOnTextComponentButton::update()
{
}

void PasteOnTextComponentButton::clickButton()
{
	if (bc->isCursorOver())
	{
		// Open clipboard
		OpenClipboard(nullptr);

		// Get handle of clipboard object for ANSI text
		HANDLE hData = GetClipboardData(CF_TEXT);

		// Lock the handle to get the actual text pointer
		auto pszText = static_cast<char*>(GlobalLock(hData));

		// Save text in a string class instance
		std::string text(pszText);

		// Release the lock
		GlobalUnlock(hData);

		// Release the clipboard
		CloseClipboard();

		tc->setTxt(text);
	}
}

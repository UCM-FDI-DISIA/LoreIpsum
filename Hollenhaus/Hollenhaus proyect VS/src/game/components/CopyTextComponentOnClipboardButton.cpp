#include <../pchs/pch.h>
#include "CopyTextComponentOnClipboardButton.h"
#include "../../sdlutils/InputHandler.h"
#include "basics/TextComponent.h"
#include "basics/BoxCollider.h"
#include <windows.h>

CopyTextComponentOnClipboardButton::CopyTextComponentOnClipboardButton(TextComponent* textComponent)
{
	tc = textComponent;
}

CopyTextComponentOnClipboardButton::~CopyTextComponentOnClipboardButton()
{
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { clickButton(); });
}

void CopyTextComponentOnClipboardButton::initComponent()
{
	bc = ent_->getComponent<BoxCollider>();
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { clickButton(); });
}

void CopyTextComponentOnClipboardButton::update()
{
}

void CopyTextComponentOnClipboardButton::clickButton()
{
	if (bc->isCursorOver())
	{
		// Se copia el contenido del TextComponent en el clipboard
		std::string textString = tc->getText();
		const char* output = textString.c_str();
		const size_t len = strlen(output) + 1;
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
		memcpy(GlobalLock(hMem), output, len);
		GlobalUnlock(hMem);
		OpenClipboard(nullptr);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hMem);
		CloseClipboard();
	}
}

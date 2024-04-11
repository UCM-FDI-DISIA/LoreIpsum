#include "pch.h"
#include "CopyTextComponentOnClipboardButton.h"
#include "../../sdlutils/InputHandler.h"
#include "basics/TextComponent.h"
#include "basics/BoxCollider.h"
#include <windows.h>

CopyTextComponentOnClipboardButton::CopyTextComponentOnClipboardButton()
{
}

CopyTextComponentOnClipboardButton::~CopyTextComponentOnClipboardButton()
{
    ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { clickButton(); });
}

void CopyTextComponentOnClipboardButton::initComponent()
{
	tc = ent_->getComponent<TextComponent>();
    bc = ent_->getComponent<BoxCollider>();
    ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { clickButton(); });
}

void CopyTextComponentOnClipboardButton::update()
{
}

void CopyTextComponentOnClipboardButton::clickButton()
{
    if (bc->isCursorOver()) {
        // Se copia el contenido del TextComponent en el clipboard
        const char* output = tc->getText().c_str();
        const size_t len = strlen(output) + 1;
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
        memcpy(GlobalLock(hMem), output, len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();
    }
}

#include "pch.h"
#include "SendInvitationButton.h"
#include "../../sdlutils/InputHandler.h"
#include "basics/BoxCollider.h"
#include "../Entity.h"
#include "SendIPFromTextComponent.h"

SendInvitationButton::SendInvitationButton()
{
}

SendInvitationButton::~SendInvitationButton()
{
    ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { clickButton(); });
}

void SendInvitationButton::initComponent()
{
    getIP = ent_->getComponent<SendIPFromTextComponent>();
    bc = ent_->getComponent<BoxCollider>();
    ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { clickButton(); });
}

void SendInvitationButton::update()
{
}

void SendInvitationButton::clickButton()
{
    getIP->sendIP();
}

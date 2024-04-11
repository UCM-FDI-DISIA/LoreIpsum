#include "pch.h"
#include "SendIPFromTextComponent.h"
#include "basics/TextComponent.h"
#include "multiplayer/NetLobby.h"

SendIPFromTextComponent::SendIPFromTextComponent(TextComponent* textComponent, NetLobby* netLobby)
{
	tc = textComponent;
	nl = netLobby;
}

SendIPFromTextComponent::~SendIPFromTextComponent()
{
}

void SendIPFromTextComponent::initComponent() 
{
}

void SendIPFromTextComponent::update()
{
}

void SendIPFromTextComponent::sendIP()
{
	nl->SendInvitation(tc->getText().c_str(), static_cast<Uint16>(2000));
}

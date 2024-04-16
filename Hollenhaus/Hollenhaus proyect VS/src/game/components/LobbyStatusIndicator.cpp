#include "pch.h"
#include "LobbyStatusIndicator.h"
#include "basics/TextComponent.h"

LobbyStatusIndicator::LobbyStatusIndicator(TextComponent* textComponent) :
	tc(textComponent)
{
}

LobbyStatusIndicator::~LobbyStatusIndicator()
{
}

void LobbyStatusIndicator::setStatus(ELobbyStatus lobbyStatus)
{
	status = lobbyStatus;

	switch (status)
	{
	case LobbyStatusIndicator::Offline:
		tc->setTxt("You are offline");
		tc->setColor(SDL_Color({ 255, 0, 0, 0 }));
		break;
	case LobbyStatusIndicator::SearchingForInvitations:
		tc->setTxt("Searching for invitations...");
		tc->setColor(SDL_Color({ 0, 0, 0, 0 }));
		break;
	case LobbyStatusIndicator::InvitationSent:
		tc->setTxt("Invitation sent correctly");
		tc->setColor(SDL_Color({ 0, 255, 0, 0 }));
		break;
	case LobbyStatusIndicator::InvitationReceived:
		tc->setTxt("InvitationReceived");
		tc->setColor(SDL_Color({ 0, 0, 255, 0 }));
		break;
	default:
		break;
	}
}

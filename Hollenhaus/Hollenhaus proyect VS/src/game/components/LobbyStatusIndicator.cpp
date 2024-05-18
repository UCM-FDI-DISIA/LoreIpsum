#include <../pchs/pch.h>
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
	case Offline:
		tc->setTxt("No estás en línea");
		tc->setColor(Colors::ROJO_PERJUICIO);
		break;
	case SearchingForInvitations:
		tc->setTxt("Buscando invitaciones...");
		tc->setColor(Colors::PEARL_CLICK);
		break;
	case InvitationSent:
		tc->setTxt("Invitación enviada correctamente");
		tc->setColor(Colors::VERDE_BANKIA);
		break;
	case InvitationReceived:
		tc->setTxt("Invitación recibida");
		tc->setColor(Colors::AMARILLO_PIS);
		break;
	default:
		break;
	}
}

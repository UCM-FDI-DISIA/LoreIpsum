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
		tc->setTxt("No est�s en l�nea");
		tc->setColor(Colors::ROJO_PERJUICIO);
		break;
	case SearchingForInvitations:
		tc->setTxt("Buscando invitaciones...");
		tc->setColor(Colors::PEARL_CLICK);
		break;
	case InvitationSent:
		tc->setTxt("Invitaci�n enviada correctamente");
		tc->setColor(Colors::VERDE_BANKIA);
		break;
	case InvitationReceived:
		tc->setTxt("Invitaci�n recibida");
		tc->setColor(Colors::AMARILLO_PIS);
		break;
	default:
		break;
	}
}

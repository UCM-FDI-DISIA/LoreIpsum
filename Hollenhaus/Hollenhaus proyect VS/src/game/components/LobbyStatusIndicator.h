#pragma once
#include "ComponentUpdate.h"

class TextComponent;
class BoxCollider;

// Este componente se encarga de almacenar el estado del lobby:
// Estados posibles:
//		Offline - No hay conexi�n a internet
//		SearchingForInvitations - El lobby est� pendiente de recibir una invitaci�n
//		InvitationSent - El lobby ha enviado una invitaci�n y esta ha llegado a su destino satisfactoriamente
//		InvitationReceived - El lobby ha recibido una invitaci�n y hay que gestionarla (aceptar / declinar)
// 
// Este componente necesita un textComponent para renderizar el estado del lobby
class LobbyStatusIndicator : public ComponentUpdate
{
public:

	enum ELobbyStatus{
		Offline,
		SearchingForInvitations,
		InvitationSent,
		InvitationReceived
	};

	LobbyStatusIndicator(TextComponent* textComponent);
	~LobbyStatusIndicator();

	void setStatus(ELobbyStatus lobbyStatus);

private:
	
	ELobbyStatus status;

	TextComponent* tc;
	
};
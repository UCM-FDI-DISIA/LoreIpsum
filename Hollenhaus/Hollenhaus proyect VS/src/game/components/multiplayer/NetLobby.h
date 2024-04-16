#pragma once
#include "../ComponentUpdate.h"
#include <SDL_net.h>

class LobbyStatusIndicator;
// NetLobby por defecto actua de server. 
// La ip se configura en la constructora para crear un masterSocket y recibir solicitudes de conexi�n
// Se crea un socketSet con dos espacios, uno de ellos ser� el masterSocket

// NetLobby tambi�n puede actuar como cliente, pero solo si se lo piden.
class NetLobby : public ComponentUpdate
{
public:
	NetLobby(Uint16 port, LobbyStatusIndicator* lobbystatus);
	~NetLobby();

	void initComponent() override;
	void update() override;

	// M�todo usado por el bot�n de enviar invitaci�n
	void SendInvitation(const char* host, const Uint16 port);

private:

	// a variable that represents the address -- in this case only the port
	IPaddress ip;

	// a socket for listening to connection requests
	TCPsocket masterSocket;

	// We want to use non-blocking communication, the way to do this is via a socket set.
	SDLNet_SocketSet socketSet;

	// a socket for sending and receiving data
	TCPsocket conn;


	ecs::entity_t acceptButton;
	ecs::entity_t declineButton;

	LobbyStatusIndicator* statusIndicator;

	// M�TODOS DEL SERVIDOR
	
		// cuando recibimos una request del cliente
		void connectToClient();

		// Called when a request is received. Triggers invitation panel
		void InstantiateInvitationPanel();

		// Invitation panel buttons
		void AcceptConection();
		void DeclineConection();


	// M�TODOS DEL CLIENTE
	
		// cuando enviamos una invitaci�n al servidor
		void connectToServer(const char* host, const int port);

		// cuando recibimos mensajes del servidor
		void ProcessServerMessages();


	// Para el cliente y el server. Lanzamos la siguiente escena
	void JumpToPregameScene(bool isHost);

	void error();
};


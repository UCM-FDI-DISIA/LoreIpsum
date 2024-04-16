#pragma once
#include "../ComponentUpdate.h"
#include <SDL_net.h>

// NetLobby por defecto actua de server. 
// La ip se configura en la constructora para crear un masterSocket y recibir solicitudes de conexión
// Se crea un socketSet con dos espacios, uno de ellos será el masterSocket

// NetLobby también puede actuar como cliente, pero solo si se lo piden.
class NetLobby : public ComponentUpdate
{
public:
	NetLobby(Uint16 port);
	~NetLobby();

	void initComponent() override;
	void update() override;

	void SendInvitation(const char* host, const Uint16 port);

private:

	// some auxiliary variables for sending/receiving information
	char buffer[256];
	int result;

	// a variable that represents the address -- in this case only the port
	IPaddress ip;

	// a socket for listening to connection requests
	TCPsocket masterSocket;

	// We want to use non-blocking communication, the way to do this is via a socket set.
	SDLNet_SocketSet socketSet;

	// a socket for sending and receiving data
	TCPsocket conn;


	// when user accepts invitation
	void connectToClient();

	// when the user wants to send invitation
	void connectToServer(const char* host, const int port);

	// Called when a request is received. Triggers invitation panel
	void InstantiateInvitationPanel();

	// Invitation panel buttons
	void AcceptConection();
	void DeclineConection();


	void error();
};


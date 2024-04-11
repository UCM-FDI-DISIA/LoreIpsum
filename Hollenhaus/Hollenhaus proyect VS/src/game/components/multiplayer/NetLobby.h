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
	NetLobby(int port);
	~NetLobby();

	void initComponent() override;
	void update() override;

	bool SendInvitation(const char* host, const int port);

private:

	// some auxiliary variables for sending/receiving information
	char buffer[256];
	int result = 0;

	// a variable that represents the address -- in this case only the port
	IPaddress ip;

	// a socket for listening to connection requests
	TCPsocket masterSocket;

	// We want to use non-blocking communication, the way to do this is via a socket set.
	SDLNet_SocketSet socketSet;

	// a socket for sending and receiving data
	TCPsocket conn;

	// called when a request is received. Triggers invitation
	bool conectionRequestedFromClient();

	// when user accepts invitation
	bool connectToClient();

	// when the user wants to send invitation
	bool connectToServer(const char* host, const int port);


	void error();
};


#include "pch.h"
#include "NetLobby.h"

using namespace std;

NetLobby::NetLobby(int port)
{

	// fill in the address in 'ip' -- note that the 2nd parameter is 'nullptr'
	// which means that we want to use 'ip' to start a server
	if (SDLNet_ResolveHost(&ip, nullptr, port) < 0) {
		error();
	}

	// Since the host in 'ip' is 0 (we provided 'nullptr' above), SDLNet_TCP_Open starts
	// a server listening at the port specified in 'ip', and returns a socket for listening
	// to connection requests
	masterSocket = SDLNet_TCP_Open(&ip);	// Esto peta. Por algún motivo el masterSocket se queda en nullptr. Creo que la ip se está seteando bien en la función anterior, asi que no sé cual es el problema....
	if (!masterSocket) {
		error();
	}

	// We want to use non-blocking communication, the way to do this is via a socket set.
	// We add sockets to this set and then we can ask if any has some activity without blocking.
	// Non-blocking communication is the adequate one for video games!
	socketSet = SDLNet_AllocSocketSet(2);

	// add the masterSocket to the set
	SDLNet_TCP_AddSocket(socketSet, masterSocket);

}

NetLobby::~NetLobby()
{
}

void NetLobby::initComponent()
{
}

void NetLobby::update()
{
	// The call to SDLNet_CheckSockets returns the number of sockets with activity
	// in socketSet. The 2nd parameter tells the method to wait up to SDL_MAX_UINT32
	// if there is no activity -- no need to put it 0 unless we really don't want to
	// block. With 0 it would consume CPU unnecessarily
	if (SDLNet_CheckSockets(socketSet, SDL_MAX_UINT32) > 0) {

		// if there is an activity in masterSocket we process it. Note that
		// before calling SDLNet_SocketReady we must have called SDLNet_CheckSockets
		if (SDLNet_SocketReady(masterSocket)) {
			conectionRequestedFromClient();
		}
	}
}

bool NetLobby::SendInvitation(const char* host, const int port)
{
	return connectToServer(host, port);
}

bool NetLobby::conectionRequestedFromClient()
{
	// TO DO it should trigger an invitation panel
	return connectToClient();	// call if invitation acepted
	// TO DO
	
}

bool NetLobby::connectToClient()
{
	if (conn = nullptr) {
		// Accept the connection (activity on master socket is always a connection request.
		// Sending and receiving data is done via the socket returned by
		// SDLNet_TCP_Accept. This way we can serve several clients.
		conn = SDLNet_TCP_Accept(masterSocket);

		// add the client to the socket
		SDLNet_TCP_AddSocket(socketSet, conn);

		// send a "connected" message to the client
		buffer[0] = 0;
		SDLNet_TCP_Send(conn, buffer, 1);
	}
	else return false;

	cout << "I AM SERVER!" << endl;
	return true;
}

bool NetLobby::connectToServer(const char* host, const int port)
{
	// fill in the address in 'ip'
	if (SDLNet_ResolveHost(&ip, host, port) < 0) {
		error();
	}

	// establish the connection with the server
	conn = SDLNet_TCP_Open(&ip);
	if (!conn) {
		error();
	}

	// Read the first byte of the server's message
	result = SDLNet_TCP_Recv(conn, buffer, 1);
	if (result < 0) {
		error(); // something went wrong
	}

	cout << "I AM CLIENT!" << endl;

	return true;
}

void NetLobby::error() {
	cout << "Error: " << SDLNet_GetError() << endl;
	exit(1);
}
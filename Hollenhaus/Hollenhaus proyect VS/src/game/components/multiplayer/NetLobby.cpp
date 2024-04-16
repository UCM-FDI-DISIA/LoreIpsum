#include "pch.h"
#include "NetLobby.h"
#include "../../gamestates/GameState.h"
#include "../../MultiplayerNamespaces.h"
#include "../basics/TextComponent.h"
#include "../Button.h"
using namespace std;

NetLobby::NetLobby(Uint16 port) :
	result(0),
	ip({0, 0}),
	masterSocket(nullptr),
	socketSet(nullptr),
	conn(nullptr)
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
	// Cerramos el masterSocket antes de salir de la escena. Solo es necesario en el lobby
	SDLNet_TCP_Close(masterSocket);
}

void NetLobby::initComponent()
{
}

void NetLobby::update()
{
	// The call to SDLNet_CheckSockets returns the number of sockets with activity in socketSet.
	// The 2nd parameter tells the method to wait if there is no activity
	// You want to put it on 0 if you dont want to block (consumes more CPU)
	if (SDLNet_CheckSockets(socketSet, 0) > 0) {

		// If there is an activity in masterSocket we process it (we act as a server)
		if (SDLNet_SocketReady(masterSocket)) {
			// Instanciamos panel de invitación
			InstantiateInvitationPanel();
			// Establecemos conexión con el cliente para enviar mensajitos
			connectToClient();
		}

		// If there is an activity in connectionSocket we process it (we act as a client)
		if (SDLNet_SocketReady(conn)) {

			// Entramos aquí si hemos enviado una invitación de conexión a otra IP
			// y la otra IP nos ha mandado un mensaje de vuelta
			// Es decir, somos clientes

			// Podemos recibir dos mensajes de vuelta:
			// Conexión aceptada
			// Conexión declinada

			NetMsgs::Msg msg;

			auto result = SDLNetUtils::receiveMsg(conn);

			msg.deserialize(result.buffer);

			switch (msg._type)
			{
			case NetMsgs::_NONE_:
				TuVieja("Mensaje : _NONE_, RECIBIDO");
				//procesar el mensaje/ lanzar error
				break;

			case NetMsgs::_INVITATION_RECEIVED_:
				TuVieja("Mensaje: EL SERVER A RECIBIDO LA INVITACIÓN");
				break;

			case NetMsgs::_ACCEPT_CONNECTION_:
				TuVieja("Mensaje : CONEXIÓN ACEPTADA, RECIBIDO");

				// Guardamos el socket del rival en la clase Data par viajar a la siguiente escena
				GameStateMachine::instance()->getCurrentState()->setSocketRival(conn);

				// Guardar que somos el host. sirve para casos concretos dentro del juego,
				// como decidir estados aleatorios por los dos. En la practica no somos host.
				GameStateMachine::instance()->getCurrentState()->setIsHost(false);

				// Ahora cambiamos de escena
				GameStateMachine::instance()->setState(GameStates::MULTIPLAYER_GAME);
				//procesar el mensaje

				break;

			case NetMsgs::_DECLINE_CONNECTION_:
				TuVieja("Mensaje : CONEXIÓN DECLINADA, RECIBIDO");

				//procesar el mensaje

				break;

			default:
				break;
			}
		}
	}

}

void NetLobby::SendInvitation(const char* host, const Uint16 port)
{
	connectToServer(host, port);
}

// Método que usa la instancia que hace de Server. Se conecta con el cliente que lo pide
void NetLobby::connectToClient()
{
	// Limpiamos el socket por si antes hubo otra conexión
	conn = nullptr;

	// Accept the connection (activity on master socket is always a connection request.
	// Sending and receiving data is done via the socket returned by
	// SDLNet_TCP_Accept. This way we can serve several clients.
	conn = SDLNet_TCP_Accept(masterSocket);

	// add the client to the socket
	SDLNet_TCP_AddSocket(socketSet, conn);

	// Avisamos al cliente de que la conexión ha sido recibida
	NetMsgs::Msg msg(NetMsgs::_INVITATION_RECEIVED_);
	SDLNetUtils::serializedSend(msg, conn);




	cout << "I AM SERVER!" << endl;
}

// Método que usa la instancia que hace de Cliente. Sirve para mandar una request al server
void NetLobby::connectToServer(const char* host, const int port)
{
	// Limpiamos el socket por si antes hubo otra conexión
	conn = nullptr;

	// fill in the address in 'ip'
	if (SDLNet_ResolveHost(&ip, host, port) < 0) {
		std::cout << "ERROR: Probablemente la ip esté mal";
		error();
	}

	// establish the connection with the server
	conn = SDLNet_TCP_Open(&ip);
	if (!conn) {
		error();
	}

	// add the server to the socket
	SDLNet_TCP_AddSocket(socketSet, conn);


	cout << "I AM CLIENT!" << endl;
}

void NetLobby::InstantiateInvitationPanel()
{
	ecs::entity_t acceptButton = Instantiate(Vector2D(100, 530));
	acceptButton->addComponent<TextComponent>("ACCEPT INV", "8bit_size_32", SDL_Color({ 0, 0,0 ,0 }), 150, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	acceptButton->addComponent<BoxCollider>();
	acceptButton->getComponent<BoxCollider>()->setSize(Vector2D(150, 40));
	acceptButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-75, -20));
	acceptButton->addComponent<Button>();
	acceptButton->getComponent<Button>()->connectToButton([this] {AcceptConection(); });

	ecs::entity_t declineButton = Instantiate(Vector2D(200, 530));
	declineButton->addComponent<TextComponent>("DECLINE INV", "8bit_size_32", SDL_Color({ 0, 0,0 ,0 }), 150, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	declineButton->addComponent<BoxCollider>();
	declineButton->getComponent<BoxCollider>()->setSize(Vector2D(150, 40));
	declineButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-75, -20));
	declineButton->addComponent<Button>();
	declineButton->getComponent<Button>()->connectToButton([this] {DeclineConection(); });
}

void NetLobby::AcceptConection()
{
	// Avisamos al cliente de que hemos aceptado la invitación de juego
	NetMsgs::Msg msg(NetMsgs::_ACCEPT_CONNECTION_);
	SDLNetUtils::serializedSend(msg, conn);

	// Guardamos el socket del rival en la clase Data par viajar a la siguiente escena
	GameStateMachine::instance()->getCurrentState()->setSocketRival(conn);

	// Guardar que somos el host. sirve para casos concretos dentro del juego,
	// como decidir estados aleatorios por los dos. En la practica no somos host.
	GameStateMachine::instance()->getCurrentState()->setIsHost(true);

	// Ahora cambiamos de escena
	GameStateMachine::instance()->setState(GameStates::MULTIPLAYER_GAME);
}

void NetLobby::DeclineConection()
{
	// Avisamos al cliente de que hemos declinado la invitación de juego
	NetMsgs::Msg msg(NetMsgs::_DECLINE_CONNECTION_);
	SDLNetUtils::serializedSend(msg, conn);

	TuVieja("Conexión DECLINADA");
}

void NetLobby::error() {
	cout << "Error: " << SDLNet_GetError() << endl;
	exit(1);
}
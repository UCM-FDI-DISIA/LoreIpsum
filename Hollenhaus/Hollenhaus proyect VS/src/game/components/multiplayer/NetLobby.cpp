#include "pch.h"
#include "NetLobby.h"
#include "../../gamestates/GameState.h"
#include "../../MultiplayerNamespaces.h"
#include "../basics/TextComponent.h"
#include "../Button.h"
#include "../LobbyStatusIndicator.h"
using namespace std;

NetLobby::NetLobby(Uint16 port, LobbyStatusIndicator* lobbyStatus) :
	ip({0, 0}),
	masterSocket(nullptr),
	socketSet(nullptr),
	conn(nullptr),
	acceptButton(nullptr),
	declineButton(nullptr),
	statusIndicator(lobbyStatus)
{	
	
	// fill in the address in 'ip' -- note that the 2nd parameter is 'nullptr'
	// which means that we want to use 'ip' to start a server
	if (SDLNet_ResolveHost(&ip, nullptr, port) < 0) {
		error();
	}

	// Since the host in 'ip' is 0 (we provided 'nullptr' above), SDLNet_TCP_Open starts
	// a server listening at the port specified in 'ip', and returns a socket for listening
	// to connection requests
	masterSocket = SDLNet_TCP_Open(&ip);
	if (!masterSocket) {
		error();
	}

	// We want to use non-blocking communication, the way to do this is via a socket set.
	// We add sockets to this set and then we can ask if any has some activity without blocking.
	// Non-blocking communication is the adequate one for video games!
	// Usamos dos sockets:
	//		Uno para el masterSocket, y actuar como servidor
	//		Otro para almacenar la conexión con el rival, y actuar de cliente
	socketSet = SDLNet_AllocSocketSet(2);

	// add the masterSocket to the set
	SDLNet_TCP_AddSocket(socketSet, masterSocket);

	// Indicamos al lobbyStatus que estamos listos para buscar invitaciones
	statusIndicator->setStatus(LobbyStatusIndicator::SearchingForInvitations);
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
	// La llamada a SDLNet_CheckSockets devuelve el número de sockets con actividad en socketSet.
	// El 2º parámetro indica al método que debe esperar si no encuentra actividad
	// 2º parámetro debe estar en 0 si no quieres bloquear el programa (consume más CPU)
	if (SDLNet_CheckSockets(socketSet, 0) > 0) {

		// Procesamos si hay actividad en el master socket (actuamos como servidor)
		if (SDLNet_SocketReady(masterSocket)) {

			// Indicamos al lobbyStatus que hemos recibido una invitación
			statusIndicator->setStatus(LobbyStatusIndicator::InvitationReceived);

			// Instanciamos panel de invitación
			InstantiateInvitationPanel();

			// Establecemos conexión con el cliente para enviar mensajitos
			connectToClient();
		}

		// Procesamos si hay actividad en el socket de conexión con el rival (actuamos como cliente)
		if (SDLNet_SocketReady(conn)) {

				// Entramos aquí si hemos enviado una invitación de conexión a otra IP
			// y la otra IP nos ha mandado un mensaje de vuelta
			// Es decir, somos clientes
			ProcessServerMessages();
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

// LLamamos al método cuando el jugador hace click en el botón para
// mandar una invitación a una IP
// Pasan cosas malas si la IP es incorrecta o no hay conexión :(
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

// Recibimos una invitación, y lanzamos un panel para que el jugador la gestione
void NetLobby::InstantiateInvitationPanel()
{
	acceptButton = Instantiate(Vector2D(100, 530));
	acceptButton->addComponent<TextComponent>("ACCEPT INV", "8bit_size_32", SDL_Color({ 0, 0,0 ,0 }), 150, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	acceptButton->addComponent<BoxCollider>();
	acceptButton->getComponent<BoxCollider>()->setSize(Vector2D(150, 40));
	acceptButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-75, -20));
	acceptButton->addComponent<Button>();
	acceptButton->getComponent<Button>()->connectToButton([this] {AcceptConection(); });

	declineButton = Instantiate(Vector2D(300, 530));
	declineButton->addComponent<TextComponent>("DECLINE INV", "8bit_size_32", SDL_Color({ 0, 0,0 ,0 }), 150, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	declineButton->addComponent<BoxCollider>();
	declineButton->getComponent<BoxCollider>()->setSize(Vector2D(150, 40));
	declineButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-75, -20));
	declineButton->addComponent<Button>();
	declineButton->getComponent<Button>()->connectToButton([this] {DeclineConection(); });
}

// Función llamada cuando aceptamos la invitación
void NetLobby::AcceptConection()
{
	// Avisamos al cliente de que hemos aceptado la invitación de juego
	NetMsgs::Msg msg(NetMsgs::_ACCEPT_CONNECTION_);
	SDLNetUtils::serializedSend(msg, conn);
	JumpToPregameScene(true);
}

// Función llamada cuando declinamos la invitación
void NetLobby::DeclineConection()
{
	// Avisamos al cliente de que hemos declinado la invitación de juego
	NetMsgs::Msg msg(NetMsgs::_DECLINE_CONNECTION_);
	SDLNetUtils::serializedSend(msg, conn);

	// Cerramos la conexión con el cliente
	SDLNet_TCP_DelSocket(socketSet, conn);
	SDLNet_TCP_Close(conn);
	conn = nullptr;

	// Eliminamos el panel de invitación
	acceptButton->setAlive(false);
	acceptButton = nullptr;
	declineButton->setAlive(false);
	declineButton = nullptr;

	// Indicamos al lobbyStatus que la invitación ha sido declinada
	statusIndicator->setStatus(LobbyStatusIndicator::SearchingForInvitations);


	TuVieja("Conexión DECLINADA");
}

// Función llamada cuando recibimos un mensaje del server
// al que hemos enviado una invitación de juego
void NetLobby::ProcessServerMessages()
{
	NetMsgs::Msg msg;
	auto result = SDLNetUtils::receiveMsg(conn);
	msg.deserialize(result.buffer);
	

	switch (msg._type)
	{
	case NetMsgs::_NONE_:
		TuVieja("Mensaje : _NONE_, RECIBIDO");

		// Procesamos el mensaje
		// Habría que lanzar error

		break;

	case NetMsgs::_INVITATION_RECEIVED_:
		TuVieja("Mensaje del server: LA INVITACIÓN HA SIDO RECIBIDA");

		// Indicamos al lobbyStatus que la invitación ha llegado con éxito a su destino
		statusIndicator->setStatus(LobbyStatusIndicator::InvitationSent);

		break;

	case NetMsgs::_ACCEPT_CONNECTION_:
		TuVieja("Mensaje del server: LA CONEXIÓN HA SIDO ACEPTADA");

		// Pasamos a la siguiente escena
		JumpToPregameScene(false);

		break;

	case NetMsgs::_DECLINE_CONNECTION_:
		TuVieja("Mensaje del server: LA CONEXIÓN HA SIDO DECLINADA");

		// Cerramos la conexión con el server 
		SDLNet_TCP_DelSocket(socketSet, conn);
		SDLNet_TCP_Close(conn);
		conn = nullptr;

		// Indicamos al lobbyStatus que la invitación ha sido declinada
		statusIndicator->setStatus(LobbyStatusIndicator::SearchingForInvitations);

		break;

	default:
		break;
	}

}

// La invitación ha sido aceptada, pasamos a la escena de PREGAME
void NetLobby::JumpToPregameScene(bool isHost)
{
	// Guardamos el socket del rival en la clase Data par viajar a la siguiente escena
	GameStateMachine::instance()->getCurrentState()->setSocketRival(conn);

	// Guardar que somos el host. sirve para casos concretos dentro del juego,
	// como decidir estados aleatorios por los dos. En la practica no somos host.
	GameStateMachine::instance()->getCurrentState()->setIsHost(isHost);

	// Ahora cambiamos de escena
	GameStateMachine::instance()->setState(GameStates::MULTIPLAYER_GAME);
}

void NetLobby::error() {
	cout << "Error: " << SDLNet_GetError() << endl;
	exit(1);
}
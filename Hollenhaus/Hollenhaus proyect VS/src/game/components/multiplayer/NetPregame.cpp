#include "pch.h"
#include "NetPregame.h"
#include "../../MultiplayerNamespaces.h"
#include "../basics/TextComponent.h"
#include "../../gamestates/GameState.h"

NetPregame::NetPregame()
{
	// Get the rival socket setted on LobbyState
	conn = GameStateMachine::instance()->getCurrentState()->getSocketRival();
		
	// add the socket to the socketSet for non-blocking communication
	SDLNet_TCP_AddSocket(socketSet, conn);
}

NetPregame::~NetPregame()
{
}

void NetPregame::initComponent()
{
	tc = ent_->getComponent<TextComponent>();
}

void NetPregame::update()
{
	// Procesamos si hay actividad en el socket de conexión con el rival (actuamos como cliente)
	if (SDLNet_SocketReady(conn)) {

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

		case NetMsgs::_READY_TO_PLAY:
		{
			TuVieja("Mensaje del rival: RIVAL SI ESTA LISTO PARA JUGAR");

			// Indicamos que el rival ya está listo para jugar
			SetRivalReady(true);

			// Procesamos los datos del mensaje (el mazo del rival)
			NetMsgs::SendMaze sendMazeMsg;
			sendMazeMsg.deserialize(result.buffer);

			// Guardamos el mazo del rival en la clase Data
			GameStateMachine::instance()->getCurrentState()->getMazeRival().clear();
			for (int i = 0; i < sendMazeMsg.size; i++) {
				GameStateMachine::instance()->getCurrentState()->getMazeRival().push_back(sendMazeMsg.maze[i]);
			}

			//DEBUG
			for (int i = 0; i < sendMazeMsg.size; i++) {
				std::cout << sendMazeMsg.maze[i] << std::endl;
			}

			// Si nosotros ya estabamos listos, comenzamos el juego
			if (GetPlayerReady()) {
				GameStateMachine::instance()->setState(GameStates::MULTIPLAYER_GAME);
			}

			break;
		}

		case NetMsgs::_NOT_READY_TO_PLAY:
			TuVieja("Mensaje del rival: RIVAL NO ESTA LISTO PARA JUGAR");

			SetRivalReady(false);

			break;

		default:
			break;
		}
	}
}

void NetPregame::SetPlayerReady(bool isReady)
{
	playerReady = isReady;

	if (isReady) {
		tc->setColor(SDL_Color({ 0, 255, 0, 0 }));
		tc->setTxt("Oponent is ready!");
	}
	else {
		tc->setColor(SDL_Color({ 255, 0, 0, 0 }));
		tc->setTxt("Oponent is NOT ready!");
	}


}

void NetPregame::PlayerReady()
{
	Uint8* maze;
	Uint8 i = 0;
	for (Uint8 e : GameStateMachine::instance()->getCurrentState()->getMaze())
	{
		maze[i] = e;
		i++;
	}

	NetMsgs::SendMaze msg(maze, i);

	SDLNetUtils::serializedSend(msg, conn);
}


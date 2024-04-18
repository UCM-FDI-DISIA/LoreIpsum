#include "pch.h"
#include "NetPregame.h"
#include "../../MultiplayerNamespaces.h"
#include "../basics/TextComponent.h"
#include "../../gamestates/GameState.h"

NetPregame::NetPregame(TextComponent* oponentReadyText, TextComponent* readyButtonText) :
	_oponentReadyText(oponentReadyText),
	_readyButtonText(readyButtonText),
	playerReady(false),
	rivalReady(false)
{

	// Get the rival socket setted on LobbyState
	conn = GameStateMachine::instance()->getCurrentState()->getSocketRival();
	socketSet = SDLNet_AllocSocketSet(1);

	// add the socket to the socketSet for non-blocking communication
	SDLNet_TCP_AddSocket(socketSet, conn);

	_oponentReadyText->setColor(SDL_Color({ 255, 0, 0, 0 }));
	_oponentReadyText->setTxt("Oponent is NOT ready!");
	_readyButtonText->setColor(SDL_Color({ 255, 0, 0, 0 }));
	_readyButtonText->setTxt("READY");
}

NetPregame::~NetPregame()
{
}


void NetPregame::update()
{

	if (SDLNet_CheckSockets(socketSet, 0) > 0) {
		TuVieja("HOLAaa");
		// Procesamos si hay actividad en el socket de conexi�n con el rival (actuamos como cliente)
		if (SDLNet_SocketReady(conn)) {
			TuVieja("HOLA");
			NetMsgs::Msg msg;
			auto result = SDLNetUtils::receiveMsg(conn);
			msg.deserialize(result.buffer);


			switch (msg._type)
			{
			case NetMsgs::_NONE_:
				TuVieja("Mensaje : _NONE_, RECIBIDO");

				// Procesamos el mensaje
				// Habr�a que lanzar error

				break;

			case NetMsgs::_READY_TO_PLAY:
			{
				TuVieja("Mensaje del rival: RIVAL SI ESTA LISTO PARA JUGAR");

				// Indicamos que el rival ya est� listo para jugar
				SetRivalReady(true);

				// Procesamos los datos del mensaje (el mazo del rival)
				NetMsgs::SendMaze sendMazeMsg;
				sendMazeMsg.deserialize(result.buffer);

				// Guardamos el mazo del rival en la clase Data
				std::vector<int> mazeRival;
				for (int i = 0; i < sendMazeMsg.size; i++) {
					mazeRival.push_back(sendMazeMsg.maze[i]);
				}
				GameStateMachine::instance()->getCurrentState()->setMazeRival(mazeRival);

				//DEBUG
				for (int i = 0; i < sendMazeMsg.size; i++) {
					std::cout << (int)(sendMazeMsg.maze[i]) << std::endl;
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
}

void NetPregame::SetPlayerReady(bool isReady)
{
	playerReady = isReady;
	if (isReady) {
		_readyButtonText->setColor(SDL_Color({ 0, 255, 0, 0 }));
		SendMsgPlayerReady();
	}
	else {
		_readyButtonText->setColor(SDL_Color({ 255, 0, 0, 0 }));
		SendMsgPlayerNotReady();
	}
	

	if (GetRivalReady()) {
		GameStateMachine::instance()->setState(GameStates::MULTIPLAYER_GAME);
	}
}

void NetPregame::SetRivalReady(bool isReady)
{
	rivalReady = isReady;

	if (isReady) {
		_oponentReadyText->setColor(SDL_Color({ 0, 255, 0, 0 }));
		_oponentReadyText->setTxt("Oponent is ready!");
	}
	else {
		_oponentReadyText->setColor(SDL_Color({ 255, 0, 0, 0 }));
		_oponentReadyText->setTxt("Oponent is NOT ready!");
	}
}

void NetPregame::SendMsgPlayerReady()
{
	Uint8 maze[100];
	Uint8 i = 0;
	for (Uint8 e : GameStateMachine::instance()->getCurrentState()->getMaze())
	{
		maze[i] = e;
		i++;
	}

	TuVieja("Mensaje con el mazo ENVIADO");

	NetMsgs::SendMaze msg(maze, i);

	SDLNetUtils::serializedSend(msg, conn);
}

void NetPregame::SendMsgPlayerNotReady()
{
	NetMsgs::Msg msg(NetMsgs::_NOT_READY_TO_PLAY);
	SDLNetUtils::serializedSend(msg, conn);
}


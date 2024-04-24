#include <../pchs/pch.h>
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
	// Obtenemos el socket del rival setteado en LobbyState y guardado en Data
	conn = GameStateMachine::instance()->getCurrentState()->getSocketRival();

	// Generamos un espacio en el socket set para el socket del rival que ya hemos obtenido
	socketSet = SDLNet_AllocSocketSet(1);

	// Aniadimos el socket del rival al socketSet para tener comunicacion no-bloqueante
	SDLNet_TCP_AddSocket(socketSet, conn);


	_oponentReadyText->setColor(SDL_Color({255, 0, 0, 0}));
	_oponentReadyText->setTxt("Oponent is NOT ready!");
	_readyButtonText->setColor(SDL_Color({255, 0, 0, 0}));
	_readyButtonText->setTxt("READY");
}


NetPregame::~NetPregame()
{
}


void NetPregame::update()
{
	// La llamada a SDLNet_CheckSockets devuelve el número de sockets con actividad en socketSet.
	// El 2º parámetro indica al método que debe esperar si no encuentra actividad
	// 2º parámetro debe estar en 0 si no quieres bloquear el programa (consume más CPU)
	if (SDLNet_CheckSockets(socketSet, 0) > 0)
	{
		// Procesamos si hay actividad en el socket de conexión con el rival (actuamos como cliente)
		if (SDLNet_SocketReady(conn))
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

			case NetMsgs::_READY_TO_PLAY:
				{
					TuVieja("Mensaje del rival: RIVAL SI ESTA LISTO PARA JUGAR");

					// Indicamos que el rival ya está listo para jugar
					SetRivalReady(true);

					// Procesamos los datos del mensaje (el mazo del rival)
					NetMsgs::SendMaze sendMazeMsg;
					sendMazeMsg.deserialize(result.buffer);

					// Guardamos el mazo del rival en la clase Data
					std::vector<int> mazeRival;
					for (int i = 0; i < sendMazeMsg.size; i++)
					{
						mazeRival.push_back(sendMazeMsg.maze[i]);
					}
					GameStateMachine::instance()->getCurrentState()->setMazeRival(mazeRival);

					// Si nosotros ya estabamos listos, comenzamos el juego
					if (GetPlayerReady())
					{
						GameStateMachine::instance()->setState(GameStates::MULTIPLAYER_GAME);
					}

					break;
				}

			case NetMsgs::_NOT_READY_TO_PLAY:

				TuVieja("Mensaje del rival: RIVAL NO ESTA LISTO PARA JUGAR");

			// Indicamos que el rival NO está listo para jugar
				SetRivalReady(false);

				break;

			default:
				break;
			}
		}
	}
}


// Cambio en nuestro estado
// Cambiamos el visual y avisamos al oponente.
void NetPregame::SetPlayerReady(bool isReady)
{
	playerReady = isReady;

	if (isReady)
	{
		_readyButtonText->setColor(SDL_Color({0, 255, 0, 0}));
		SendMsgPlayerReady();
	}
	else
	{
		_readyButtonText->setColor(SDL_Color({255, 0, 0, 0}));
		SendMsgPlayerNotReady();
	}

	// Si estamos listos y nuestro oponente también estaba listo, cambio de escena
	if (GetRivalReady())
	{
		GameStateMachine::instance()->setState(GameStates::MULTIPLAYER_GAME);
	}
}


// Cambio en el estado del oponente
// Simplemente modificamos los visuales
// Update() se engarga de procesar el mensaje del oponente
void NetPregame::SetRivalReady(bool isReady)
{
	rivalReady = isReady;

	if (isReady)
	{
		_oponentReadyText->setColor(SDL_Color({0, 255, 0, 0}));
		_oponentReadyText->setTxt("Oponent is ready!");
	}
	else
	{
		_oponentReadyText->setColor(SDL_Color({255, 0, 0, 0}));
		_oponentReadyText->setTxt("Oponent is NOT ready!");
	}
}


// Avisamos al oponente que estamos listos.
// Le enviamos nuestro mazo
void NetPregame::SendMsgPlayerReady()
{
	// Generamos los datos que pide el constructor del mensaje para enviar el mazo
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


// Avisamos al oponente que NO estamos listos
void NetPregame::SendMsgPlayerNotReady()
{
	NetMsgs::Msg msg(NetMsgs::_NOT_READY_TO_PLAY);
	SDLNetUtils::serializedSend(msg, conn);
}

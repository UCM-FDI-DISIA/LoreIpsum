#include "pch.h"
#include "NetEndGame.h"
#include "../../gamestates/GameState.h"

#include "../../MultiplayerNamespaces.h"


NetEndGame::NetEndGame()
{
	rival = GameStateMachine::instance()->getCurrentState()->getSocketRival();

	//creacion del socketSet
	socketSet = SDLNet_AllocSocketSet(1);

	// añadir el socker al sockerSet
	SDLNet_TCP_AddSocket(socketSet, rival);
}

NetEndGame::~NetEndGame()
{
}

void NetEndGame::initComponent()
{
}

void NetEndGame::update()
{
	//recibir y procesar mensajes
	if (SDLNet_CheckSockets(socketSet, 0) > 0) {

		if (SDLNet_SocketReady(rival)) {

			NetMsgs::Msg msg;

			auto result = SDLNetUtils::receiveMsg(rival);

			msg.deserialize(result.buffer);

			switch (msg._type)
			{
			case NetMsgs::_NONE_:
				TuVieja("Mensaje : _NONE_, RECIBIDO");

				//procesar el mensaje/ lanzar error
				break;
			default:
				break;
			}
		}
	}
}

void NetEndGame::playAgain()
{
	TuVieja("Boton de jugar otra vez pulsado");

	//ir al menu de MultiplayerGame(sin cerrar el socket del rival)
	//se cierra el socketSet
}

void NetEndGame::changeMaze()
{

	TuVieja("Boton de cambiar mazo pulsado");

	//ir al menu de MultiplayerPreGame(sin cerrar el socket del rival)
	//se cierra el socket set
}

void NetEndGame::exit()
{
	TuVieja("Boton de salir pulsado");

	//cerrar socket del rival y el socketSet


	//ir al menu principal
	GameStateMachine::instance()->setState(GameStates::MAINMENU);
}

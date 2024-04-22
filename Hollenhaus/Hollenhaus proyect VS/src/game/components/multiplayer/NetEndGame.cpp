#include <../pchs/pch.h>
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
			case NetMsgs::_EXIT_END_GAME_:
				TuVieja("Mensaje : _EXIT_END_GAME_, RECIBIDO");

				//procesar el mensaje/ lanzar error
				//cerrar socket del rival y el socketSet
				SDLNet_TCP_Close(rival);
				SDLNet_FreeSocketSet(socketSet);

				//ir al menu principal
				GameStateMachine::instance()->setState(GameStates::MAINMENU);
				break;
			case NetMsgs::_CHANGE_MAZE_END_GAME_:
				TuVieja("Mensaje : _CHANGE_MAZE_END_GAME_, RECIBIDO");

				//swapea el estado de mazeChangeSelected del rival
				rivalChangeMazeSelected = !rivalChangeMazeSelected;

				//si los 2 queremos ir al estado,cambiamos de estado
				if (rivalChangeMazeSelected && changeMazeSelected) {
					//mandar mensaje de cambio de estado
					NetMsgs::Msg changeState = NetMsgs::Msg(NetMsgs::_CHANGE_STATE_PREGAME_END_GAME_);
					SDLNetUtils::serializedSend(changeState, rival);

					//ir al menu de MultiplayerPreGame(sin cerrar el socket del rival)
					GameStateMachine::instance()->setState(GameStates::MULTIPLAYER_LOBBY);//cambiar por preGame cuando se mergee la rama
					
					//se cierra el socket set
					SDLNet_FreeSocketSet(socketSet);
				}
				break;
			case NetMsgs::_PLAY_AGAIN_END_GAME_:
				TuVieja("Mensaje : _PLAY_AGAIN_END_GAME_, RECIBIDO");

				//swap del estado del boton
				rivalPlayAgainSelected = !rivalPlayAgainSelected;

				if (rivalPlayAgainSelected && playAgainSelected) {

					//mandar mensaje de cambio de estado
					NetMsgs::Msg changeState = NetMsgs::Msg(NetMsgs::_CHANGE_STATE_GAME_END_GAME_);
					SDLNetUtils::serializedSend(changeState, rival);

					//ir al menu de MultiplayerPreGame(sin cerrar el socket del rival)
					GameStateMachine::instance()->setState(GameStates::MULTIPLAYER_GAME);
					//se cierra el socket set
					SDLNet_FreeSocketSet(socketSet);
				}
				break;
			case NetMsgs::_CHANGE_STATE_PREGAME_END_GAME_:
				TuVieja("Mensaje : _CHANGE_STATE_PREGAME_END_GAME_, RECIBIDO");
				GameStateMachine::instance()->setState(GameStates::MULTIPLAYER_LOBBY);//cambiar por preGame cuando se mergee la rama
				break;
			case NetMsgs::_CHANGE_STATE_GAME_END_GAME_:
				TuVieja("Mensaje : _CHANGE_STATE_GAME_END_GAME_, RECIBIDO");
				GameStateMachine::instance()->setState(GameStates::MULTIPLAYER_GAME);
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

	//swap del estado 
	playAgainSelected = !playAgainSelected;

	//enviar el mensaje de que se ha pulsado el boton
	NetMsgs::Msg msg = NetMsgs::Msg(NetMsgs::_PLAY_AGAIN_END_GAME_);
	SDLNetUtils::serializedSend(msg, rival);
}

void NetEndGame::changeMaze()
{
	TuVieja("Boton de cambiar mazo pulsado");

	//swapea el estado de mazeChangeSelected
	changeMazeSelected = !changeMazeSelected;

	//enviar el mensaje de que se ha pulsado el boton
	NetMsgs::Msg msg = NetMsgs::Msg(NetMsgs::_CHANGE_MAZE_END_GAME_);
	SDLNetUtils::serializedSend(msg, rival);
}


void NetEndGame::exit()
{
	TuVieja("Boton de salir pulsado");

	//enviar mensaje de salir del menu
	NetMsgs::Msg exit = NetMsgs::Msg(NetMsgs::_EXIT_END_GAME_);
	SDLNetUtils::serializedSend(exit, rival);

	//cerrar socket del rival y el socketSet
	SDLNet_TCP_Close(rival);
	SDLNet_FreeSocketSet(socketSet);

	//ir al menu principal
	GameStateMachine::instance()->setState(GameStates::MAINMENU);
}

bool NetEndGame::getPlayAgainSelected()
{
	return playAgainSelected;
}

bool NetEndGame::getChangeMazeSelected()
{
	return changeMazeSelected;
}

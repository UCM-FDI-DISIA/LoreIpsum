#pragma once

#include "../sdlutils/SDLNetUtils.h"
#include "../utils/Vector2D.h"


namespace NetMsgs
{
	enum MsgType : Uint8
	{
		_NONE_,
		_INVITATION_RECEIVED_,
		// 
		_ACCEPT_CONNECTION_,
		//
		_DECLINE_CONNECTION_,
		//
		_READY_TO_PLAY,
		//
		_NOT_READY_TO_PLAY,
		//W
		_PLAY_CARD_,
		//
		_DRAW_CARD_,
		//
		_CHANGE_TURN_,
		//
		_END_GAME_,
		//
		_FIRST_TURN_OWNER_,
		//
		_EXIT_END_GAME_,
		//
		_CHANGE_MAZE_END_GAME_,
		//
		_PLAY_AGAIN_END_GAME_,
		//
		_CHANGE_STATE_PREGAME_END_GAME_,
		//
		_CHANGE_STATE_GAME_END_GAME_,
		//
	};

	struct Msg
	{
		Msg(MsgType type) : _type(type)
		{
		}

		Msg(): _type(_NONE_)
		{
		};

		Uint8 _type;

		_IMPL_SERIALIAZION_(_type)
	};

	// Mensaje para enviar tu mazo al rival cuando estes listo para jugar
	struct SendMaze : Msg
	{
		SendMaze()
		{
		};

		SendMaze(Uint8 _maze[], Uint8 _size)
		{
			for (Uint8 i = 0; i < _size; i++)
				maze[i] = _maze[i];
			size = _size;
			_type = _READY_TO_PLAY;
		}

		// El mazo se envia en un array de tamanio fijo ya que es la única forma posible
		// segun la implementación de SDLNetUtils
		// Tamanio 100 ya que no debería haber un mazo de mayor tamanio.
		Uint8 maze[100];
		Uint8 size;

		// Importante enviar el tamanio del array justo detrás del mismo. 
		// Mas importante aun especificar que el tamanio es unsigned (u). Sino, no compila.
		_IMPL_SERIALIAZION_WITH_BASE_(Msg, maze, 100u, size)
	};

	struct PlayCard : Msg
	{
		PlayCard()
		{
		};

		PlayCard(int index, Vector2D pos)
			: index(index), posX(pos.getX()), posY(pos.getY())
		{
			_type = _PLAY_CARD_;
		}

		Uint8 index;

		Uint8 posX;
		Uint8 posY;


		_IMPL_SERIALIAZION_WITH_BASE_(Msg, index, posX, posY)
	};


	struct FirstTurn : Msg
	{
		FirstTurn()
		{
		};

		FirstTurn(Uint8 myMultiplayerTurn)
			: myMultiplayerTurn(myMultiplayerTurn)
		{
			_type = _FIRST_TURN_OWNER_;
		};

		Uint8 myMultiplayerTurn;

		_IMPL_SERIALIAZION_WITH_BASE_(Msg, myMultiplayerTurn)
	};
}

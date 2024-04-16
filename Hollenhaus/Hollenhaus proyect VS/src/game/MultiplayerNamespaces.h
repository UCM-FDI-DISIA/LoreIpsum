#pragma once

#include "../sdlutils/SDLNetUtils.h"
#include "../utils/Vector2D.h"


namespace NetMsgs {

	enum MsgType : Uint8 {
		_NONE_,
		_INVITATION_RECEIVED_, //
		_ACCEPT_CONNECTION_, //
		_DECLINE_CONNECTION_, //
		_PLAY_CARD_ , //
		_DRAW_CARD_, //
		_CHANGE_TURN_, //
		_END_GAME_, //
		_FIRST_TURN_OWNER_ //
	};

	struct Msg {

		Msg(MsgType type) : _type(type){}

		Msg():_type(_NONE_) {};

		Uint8 _type;

		_IMPL_SERIALIAZION_(_type)
	};

	struct PlayCard : Msg {

		PlayCard() {};
		PlayCard(int index, Vector2D pos)
			:index(index), posX(pos.getX()), posY(pos.getY()) 
		{
			_type = _PLAY_CARD_;

		}

		Uint8 index;

		Uint8 posX;
		Uint8 posY;


		_IMPL_SERIALIAZION_WITH_BASE_(Msg, index, posX, posY)
	};


	struct FirstTurn : Msg {

		FirstTurn() {};
		FirstTurn(Uint8 myMultiplayerTurn)
		:myMultiplayerTurn(myMultiplayerTurn)
		{
			_type = _FIRST_TURN_OWNER_;
		};
		
		Uint8 myMultiplayerTurn;

		_IMPL_SERIALIAZION_WITH_BASE_(Msg, myMultiplayerTurn)
	};
}

#pragma once

#include "../sdlutils/SDLNetUtils.h"
#include "../utils/Vector2D.h"


namespace MultiplayerStructs {

	enum MsgType : Uint8 {
		_NONE_,
		_PLAY_CARD_ , //
		_DRAW_CARD_, //
		_CHANGE_TURN_, //
		_END_GAME_ //
	};

	struct Msg {

		Msg(MsgType type) : _type(type){}

		Msg():_type(_NONE_) {};

		Uint8 _type;

		_IMPL_SERIALIAZION_(_type)
	};

	struct PlayCard : Msg {

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

}

#pragma once

namespace Cards
{
	enum State {
		ON_HAND,
		ON_HOVER,
		ON_DRAG,
		ON_CELL,
		ON_DECK
	};
}

namespace Turns
{
	enum State {
        J1,
        J2,
        Finish
    };
}

namespace Effects {
	enum Direction
	{
		Up,
		Right,
		Down,
		Left,
		None
	};

	enum Type
	{
		Esquina,		// 0
		Centro,			// 1
		Flecha,			// 2
		Superflecha,	// 3
		Block,			// 4
		Unblockable,

		_NO_DISCARD_
	};
}

namespace Players
{
	enum Owner
	{
		NONE,
		PLAYER1,
		PLAYER2,
		NULO
	};
}

namespace Text
{
	enum BoxPivotPoint {
		LeftTop,
		LeftCenter,
		LeftBot,
		RightTop,
		RightCenter,
		RightBot,
		CenterTop,
		CenterCenter,
		CenterBot
	};

	enum TextAlignment {
		Left,
		Center,
		Right
	};
}
#pragma once

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

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
		PLAYER1,//jugador?
		PLAYER2,//IA?
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

namespace JsonData
{
	/// CARD DATA STRUCT
	struct CardEffect
	{
		using Directions = std::vector<Effects::Direction>;

		CardEffect();
		CardEffect(Effects::Type t, int v, Directions& d)
			: type_(t), value_(v), directions_(d) {}

		Effects::Type type() const	{ return type_; }
		int value() const	{ return value_; }
		Directions directions() const { return directions_; }

	private:
		Effects::Type type_;
		int value_;
		Directions directions_;
	};

	struct CardData
	{ 
		CardData();
		CardData(int c, int v, std::string& s, bool u, std::vector<CardEffect>& e)
			: cost_(c), value_(v), sprite_(s), unblockable_(u), effects_(e) {}

		// getters con nombres simplificados para mas facil acceso desde sdlutils
		int cost() const			{ return cost_; }
		int value() const			{ return value_; }
		std::string& sprite()		{ return sprite_; }
		bool unblockable() const	{ return unblockable_; }
		std::vector<CardEffect>& effects() { return effects_; }

	private:
		int cost_;
		int value_;
		std::string sprite_;
		bool unblockable_;
		std::vector<CardEffect> effects_;
	};

	struct DialogueData {
		DialogueData();
		DialogueData(std::string text) 
			:text_(text){};

		std::string text() { return text_; };

	private:
		std::string text_;
	};
}
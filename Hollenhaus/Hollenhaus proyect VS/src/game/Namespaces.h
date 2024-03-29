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

namespace DialogueEvents 
{
	enum Events {
		None,				// No ocurre nada
		ChangeScene,		// Evento para cambiar de escena
		StartAnimation,		// Evento para lanzar una animación
		ConfirmMatchPopUp	// Evento para mostrar una ventana donde el jugador acepta o rechaza una partida inminente
	};
}

namespace JsonData
{
	/// CARD DATA STRUCT
	struct CardEffect
	{
		using Directions = std::vector<Effects::Direction>;

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

	struct CardData {
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

	struct DialogueEventS {
		DialogueEventS();
		DialogueEventS(int tg, int t, int s) :
			timing(tg),
			type(t),
			scene(s) 
		{};

	private:
		int timing, type;
		int scene;

	};


	struct NodeData {
		NodeData();
		NodeData(const int nodeID, const std::string& text, const DialogueEvents::Events nodeEventsStart, 
			const DialogueEvents::Events nodeEventsFinish, std::vector<DialogueEventS>& es) :
			nodeID_(nodeID),
			text_(text),
			eventStart_(nodeEventsStart),
			eventFinish_(nodeEventsFinish),
			eventsStart_(es)
		{};

		int NodeID() { return nodeID_; }
		std::string& Text() { return text_; }
		DialogueEvents::Events NodeEventStart() { return eventStart_; }
		DialogueEvents::Events NodeEventFinish() { return eventFinish_; }

	private:
		int nodeID_;
		std::string text_;
		DialogueEvents::Events eventStart_;
		DialogueEvents::Events eventFinish_;

		std::vector<DialogueEventS> eventsStart_;
	};

	struct ConvoData {
		ConvoData();
		ConvoData(const int convoID, const std::vector<NodeData>& nodes) :
			convoID_(convoID),
			nodes_(nodes)
		{};

		int ConvoID() { return convoID_; }
		std::vector<NodeData>& NodesVector() { return nodes_; }
		NodeData& Node(int n) { return nodes_[n]; }

	private:
		int convoID_;
		std::vector<NodeData> nodes_;
	};

	// Cada instancia de DialogueData es un owner con todas sus conversaciones y nodos correspondientes a cada conversacion
	struct DialogueData {
		DialogueData();
		DialogueData(const std::string& NPCName, const std::vector<ConvoData>& convos) :
			NPCName_(NPCName),
			convos_(convos)
		{};

		std::string& NPCName() { return NPCName_; }
		std::vector<ConvoData>& ConvosVector() { return convos_; }
		ConvoData& Convo(int n) { return convos_[n]; }
	private:
		std::string NPCName_;
		std::vector<ConvoData> convos_;

	};

}
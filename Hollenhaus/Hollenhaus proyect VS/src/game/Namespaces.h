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
        Finish,
		IA
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
		NULO,
		IA
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

		int getType() { return type; }
		int getScene() { return scene; }

	private:
		int timing, type;
		int scene;

	};


	struct NodeData {
		NodeData();
		NodeData(const int nodeID, const std::string& text, const DialogueEvents::Events nodeEventsStart, 
			const DialogueEvents::Events nodeEventsFinish, std::vector<DialogueEventS>& es, std::vector<DialogueEventS>& ef) :
			nodeID_(nodeID),
			text_(text),
			eventStart_(nodeEventsStart),
			eventFinish_(nodeEventsFinish),
			eventsStart_(es),
			eventsFinish_(ef)
		{};

		int NodeID() { return nodeID_; }
		std::string& Text() { return text_; }
		DialogueEvents::Events NodeEventStart() { return eventStart_; }
		DialogueEvents::Events NodeEventFinish() { return eventFinish_; }
		std::vector<DialogueEventS> NodeEventsStart() { return eventsStart_; }
		std::vector<DialogueEventS> NodeEventsFinish() { return eventsFinish_; }

	private:
		int nodeID_;
		std::string text_;
		DialogueEvents::Events eventStart_;
		DialogueEvents::Events eventFinish_;

		std::vector<DialogueEventS> eventsStart_;
		std::vector<DialogueEventS> eventsFinish_;
	};

	struct ConvoData {
		ConvoData();
		ConvoData(const int convoID, const bool autoc, const std::vector<NodeData>& nodes) :
			convoID_(convoID), auto_(autoc),
			nodes_(nodes)
		{};

		int ConvoID() { return convoID_; }
		std::vector<NodeData>& NodesVector() { return nodes_; }
		NodeData& Node(int n) { return nodes_[n]; }
		bool isAuto() { return auto_; }

	private:
		int convoID_;
		bool auto_;
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
		int ID() { return NPCID_; }
	private:
		std::string NPCName_;
		int NPCID_;
		std::vector<ConvoData> convos_;

	};

	struct NPCData {
		NPCData();
		NPCData(int id, std::string name, std::string s, float sx, float sy, int px, float py, float t, int scen, int lay) :
			NPCID_(id), name(name), sprite(s), scaleX(sx), scaleY(sy), posX(px), posY(py), type(t), scene(scen), layer(lay) 
		{};

		int getID() { return NPCID_; }
		std::string getName() { return name; }
		std::string getSprite() { return sprite; }
		Vector2D getScale() { return { scaleX, scaleY }; }
		Vector2D getPos() { return { posX, posY }; }
		int getType() { return type; }
		int getScene() { return scene; }
		int getLayer() { return layer; }


	private:
		int NPCID_;
		std::string name;
		std::string sprite;
		float scaleX, scaleY;
		float posX, posY;
		int type;
		int scene;
		int layer;

	};

	struct KeyData {
		KeyData() {};
		KeyData(std::string text) : text_(text) {};

		std::string text() { return text_; }
	private:
		std::string text_;
	};

}
#pragma once

//Checkml
#include <game/checkML.h>

namespace Colors
{
	constexpr SDL_Color ROJO_HOLLENHAUS = {148, 47, 55, 255};
	constexpr SDL_Color AMARILLO_PIS = {191, 180, 138, 255};
	// blancos
	constexpr SDL_Color PEARL_HOLLENHAUS = {226, 223, 210, 255};
	constexpr SDL_Color PEARL_CLICK = {250, 248, 240, 255};
	// negros
	constexpr SDL_Color MIDNIGHT_HOLLENHAUS = {16, 23, 32, 255}; // texto color normal
	constexpr SDL_Color MIDNIGHT_CLICK = {49, 50, 78, 255}; // click texto color
	constexpr SDL_Color MIDNIGHT_HOVER = {73, 21, 31, 255}; // hover texto color
}

namespace Fonts
{
	const std::string GROTESK_8 = "space_grotesk_bold_8";
	const std::string GROTESK_16 = "space_grotesk_bold_16";
	const std::string GROTESK_24 = "space_grotesk_bold_24";
	const std::string GROTESK_32 = "space_grotesk_bold_32";
	const std::string GROTESK_40 = "space_grotesk_bold_40";
	const std::string BIT_8 = "8bit_size_8";
	const std::string BIT_16 = "8bit_size_16";
	const std::string BIT_24 = "8bit_size_24";
	const std::string BIT_32 = "8bit_size_32";
	const std::string BIT_40 = "8bit_size_40";
}

namespace Cards
{
	enum State
	{
		ON_HAND,
		ON_HOVER,
		ON_DRAG,
		ON_CELL,
		ON_DECK
	};
}

namespace Turns
{
	enum State
	{
		J1,
		J2,
		Finish,
		IA,
		J2_MULTIPLAYER
	};
}

namespace Effects
{
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
		Esquina,
		// 0
		Centro,
		// 1
		Flecha,
		// 2
		Superflecha,
		// 3
		Block,
		// 4
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
		//jugador?
		PLAYER2,
		//IA?
		PLAYER2_MULTIPLAYER,
		NULO,
		IA
	};
}

namespace Text
{
	enum BoxPivotPoint
	{
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

	enum TextAlignment
	{
		Left,
		Center,
		Right
	};
}

namespace DialogueEvents
{
	enum Events
	{
		None,
		// No ocurre nada
		ChangeScene,
		// Evento para cambiar de escena
		StartAnimation,
		// Evento para lanzar una animaci�n
		ConfirmMatchPopUp,
		// Evento para mostrar una ventana donde el jugador acepta o rechaza una partida inminente
		ActionEnded
	};
}

namespace JsonData
{
	/// CARD DATA STRUCT
	struct CardEffect
	{
		using Directions = std::vector<Effects::Direction>;

		CardEffect(Effects::Type t, int v, Directions& d)
			: type_(t), value_(v), directions_(d)
		{
		}

		Effects::Type type() const { return type_; }
		int value() const { return value_; }
		Directions directions() const { return directions_; }

	private:
		Effects::Type type_;
		int value_;
		Directions directions_;
	};

	struct CardData
	{
		CardData();

		CardData(int id, int c, int v, std::string& s, bool u, std::vector<CardEffect>& e)
			: id_(id), cost_(c), value_(v), sprite_(s), unblockable_(u), effects_(e)
		{
		}

		// getters con nombres simplificados para mas facil acceso desde sdlutils
		int id() const { return id_; }
		int cost() const { return cost_; }
		int value() const { return value_; }
		std::string& sprite() { return sprite_; }
		bool unblockable() const { return unblockable_; }
		std::vector<CardEffect>& effects() { return effects_; }

	private:
		int id_;
		int cost_;
		int value_;
		std::string sprite_;
		bool unblockable_;
		std::vector<CardEffect> effects_;
	};

	struct DialogueEventS
	{
		DialogueEventS();

		DialogueEventS(int tg, int t, int s, int gd, int rd) :
			timing(tg),
			type(t),
			scene(s),
			greenDecision(gd),
			redDecision(rd)
		{
		};

		int getType() { return type; }
		int getScene() { return scene; }
		int getGreenDecision() { return greenDecision; }
		int getredDecision() { return redDecision; }

	private:
		int timing, type;
		int scene;
		int greenDecision, redDecision;
	};


	struct NodeData
	{
		NodeData();

		NodeData(const int nodeID, const std::string& text, const DialogueEvents::Events nodeEventsStart,
		         const DialogueEvents::Events nodeEventsFinish, std::vector<DialogueEventS>& es,
		         std::vector<DialogueEventS>& ef) :
			nodeID_(nodeID),
			text_(text),
			eventStart_(nodeEventsStart),
			eventFinish_(nodeEventsFinish),
			eventsStart_(es),
			eventsFinish_(ef)
		{
		};

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

	struct ConvoData
	{
		ConvoData();

		ConvoData(const int convoID, const bool autoc, const std::vector<NodeData>& nodes) :
			convoID_(convoID), auto_(autoc),
			nodes_(nodes)
		{
		};

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
	struct DialogueData
	{
		DialogueData();

		DialogueData(const std::string& NPCName, const std::vector<ConvoData>& convos) :
			NPCName_(NPCName),
			convos_(convos)
		{
		};

		std::string& NPCName() { return NPCName_; }
		std::vector<ConvoData>& ConvosVector() { return convos_; }
		ConvoData& Convo(int n) { return convos_[n]; }
		int ID() { return NPCID_; }

	private:
		std::string NPCName_;
		int NPCID_;
		std::vector<ConvoData> convos_;
	};

	struct NPCData
	{
		NPCData();

		NPCData(int id, std::string name, std::string s, std::string shine, float sx, float sy, int px, float py,
		        float t, int scen, int lay) :
			NPCID_(id), name(name), sprite(s), shineSprite(shine), scaleX(sx), scaleY(sy), posX(px), posY(py), type(t),
			scene(scen), layer(lay)
		{
		};

		int getID() { return NPCID_; }
		std::string getName() { return name; }
		std::string getSprite() { return sprite; }
		std::string shine() { return shineSprite; }
		Vector2D getScale() { return {scaleX, scaleY}; }
		Vector2D getPos() { return {posX, posY}; }
		int getType() { return type; }
		int getScene() { return scene; }
		int getLayer() { return layer; }

	private:
		int NPCID_;
		std::string name;
		std::string sprite;
		std::string shineSprite;
		float scaleX, scaleY;
		float posX, posY;
		int type;
		int scene;
		int layer;
	};

	struct KeyData
	{
		KeyData()
		{
		};

		KeyData(std::string text) : text_(text)
		{
		};

		std::string text() { return text_; }

	private:
		std::string text_;
	};
}

namespace Tutorials
{
	enum Tutorials
	{
		BOARD,
		DECKBUILDER,
	};

	enum Board
	{
		BOARD_NONE,
		INIT,
		CARD,
		CARD_COST,
		CARD_POINTS,
		CARD_IMAGE,
		DECK,
		DRAW_CARD,
		CELL,
		PLACE_CARD,
		POINTS,
		ACTION,
		ACTION_PTS,
		NEXT_TURN,
		PRESS_NEXT_TURN,
		AI_TURN,
		NEXT_CARD_1,
		EFFECTS_PT1,
		END_TUTORIAL,
		FREEDOM
	};

	enum Deckbuilder
	{
		DECKBUILDER_NONE
	};
}

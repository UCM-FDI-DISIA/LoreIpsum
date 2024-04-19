#pragma once



class CardFactory;
class FakeCardFactory;
class HandFactory;
class BoardFactory;
class MatchStateUIFactory;
class DialogueFactory;
class NPCFactory;
class DecisionFactory;


namespace ecs {
	class Entity;
	using entity_t = Entity*;
}


class Factory
{
public:



#pragma region Templates setFactories
	/*
		Si se a�ade un nuevo tipo de factory para objetos en especifico,
		hay que meter una nueva variable de ese tipo en esta clase y crear una
		sobrecarga de este metodo con template como las que est�n ya hechas
	*/


	template<typename ...Ts>
	void SetFactories(Ts &&... args) {};


	template<typename ...Ts>
	void SetFactories(BoardFactory* bf, Ts &&... args) {
		boardFactory = bf;
		SetFactories(std::forward<Ts>(args)...);
	}


	template<typename ...Ts>
	void SetFactories(CardFactory* cf, Ts &&... args) {
		cardFactory = cf;
		SetFactories(std::forward<Ts>(args)...);
	}

	template<typename ...Ts>
	void SetFactories(MatchStateUIFactory* msUIf, Ts &&... args) {
		matchStateUIFactory = msUIf;
		SetFactories(std::forward<Ts>(args)...);
	}

	template<typename ...Ts>
	void SetFactories(FakeCardFactory* fcf, Ts &&... args) {
		fakeCardFactory = fcf;
		SetFactories(std::forward<Ts>(args)...);
	}

	template<typename ...Ts>
	void SetFactories(DialogueFactory* df, Ts &&... args) {
		dialogueFactory = df;
		SetFactories(std::forward<Ts>(args)...);
	}

	template<typename ...Ts>
	void SetFactories(NPCFactory* npcf, Ts &&... args) {
		npcFactory = npcf;
		SetFactories(std::forward<Ts>(args)...);
	}

	template<typename ...Ts>
	void SetFactories(DecisionFactory* decisionF, Ts &&... args) {
		decisionFactory = decisionF;
		SetFactories(std::forward<Ts>(args)...);
	}
		

#pragma endregion

	Factory() : 
	boardFactory(nullptr),
	cardFactory(nullptr),
	handFactory(nullptr),
	matchStateUIFactory(nullptr),
	dialogueFactory(nullptr),
	npcFactory(nullptr),
	fakeCardFactory(nullptr),
	decisionFactory(nullptr)

	{};


	ecs::entity_t createCard(int id, Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<JsonData::CardEffect>& effects);
	ecs::entity_t createFakeCard(int id, Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<JsonData::CardEffect>& effects);

	ecs::entity_t createDropDetector(Vector2D pos);

	ecs::entity_t createHand();
	ecs::entity_t createDeck();
	ecs::entity_t createDeckJ2();
	ecs::entity_t createBoard();

	// M�todos para crear la UI en el MatchState
	ecs::entity_t createVisual_EndTurnButton(int posX, int posY);
	ecs::entity_t createVisual_ActionPointsCounter(int posX, int posY);
	ecs::entity_t createVisual_ScoreCounter(int posX, int posY, SDL_Color color);
	ecs::entity_t createVisual_PlayerTurnIndicator(int posX, int posY);
	ecs::entity_t createVisual_BackgroundBlackBox(int posX, int posY, float xPixelsSize, float yPixelsSize);
	ecs::entity_t createVisual_BackgroundFullImage();

	// metodos para los NPCs
	// i de index para especificar el npc que quieres crear del json
	ecs::entity_t createNPC(int i, ecs::entity_t parent);

	// metodos para los dialogos
	ecs::entity_t createDialogue(std::string id, int convo, int node, Vector2D pos, Vector2D size,
		int speed, int cooldown, ecs::entity_t parent, int layer, bool auto_, std::string fontID, SDL_Color color, Uint32 wrapLenght, Text::BoxPivotPoint boxPivotPoint,
		Text::TextAlignment textAlignment);

	// metodos para las decisiones al acabar dialogo
	void createDecision(Vector2D pos, Vector2D size, ecs::entity_t parent, int layer, int scene, int greenDecision, int redDecision,
		std::string fontID, SDL_Color color, Uint32 wrapLenght, Text::BoxPivotPoint boxPivotPoint, Text::TextAlignment textAlignment);


public:

	BoardFactory* boardFactory;
	CardFactory* cardFactory;
	HandFactory* handFactory;
	MatchStateUIFactory* matchStateUIFactory;
	DialogueFactory* dialogueFactory;
	NPCFactory* npcFactory;
	FakeCardFactory* fakeCardFactory;
	DecisionFactory* decisionFactory;
};


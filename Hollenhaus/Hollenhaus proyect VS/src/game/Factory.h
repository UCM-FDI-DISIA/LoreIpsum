#pragma once



class CardFactory;
class HandFactory;
class BoardFactory;
class MatchStateUIFactory;

namespace ecs {
	class Entity;
	using entity_t = Entity*;
}


class Factory
{
public:


	
#pragma region Templates setFactories
	/*
		Si se añade un nuevo tipo de factory para objetos en especifico,
		hay que meter una nueva variable de ese tipo en esta clase y crear una
		sobrecarga de este metodo con template como las que están ya hechas
	*/

	
	template<typename ...Ts>
	void SetFactories(Ts &&... args){};
	

	template<typename ...Ts>
	void SetFactories(BoardFactory* bf, Ts &&... args) {
		boardFactory = bf;
		SetFactories(std::forward<Ts>(args)...);
	}

	
	template<typename ...Ts>
	void SetFactories(CardFactory* cf, Ts &&... args) {
		cardFactory =cf;
		SetFactories(std::forward<Ts>(args)...);
	}
	
	template<typename ...Ts>
	void SetFactories(MatchStateUIFactory* msUIf, Ts &&... args) {
		matchStateUIFactory = msUIf;
		SetFactories(std::forward<Ts>(args)...);
	}
		

#pragma endregion

	Factory() : 
	boardFactory(nullptr),
	cardFactory(nullptr),
	handFactory(nullptr),
	matchStateUIFactory(nullptr)
	{};


	ecs::entity_t createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<SDLUtils::CardEffect>& effects);

	ecs::entity_t createDropDetector(Vector2D pos);

	ecs::entity_t createHand();
	void createDeck();
	void createDeckJ2();
	ecs::entity_t createBoard();

	// Métodos para crear la UI en el MatchState
	ecs::entity_t createVisual_EndTurnButton(int posX, int posY);
	ecs::entity_t createVisual_ActionPointsCounter(int posX, int posY);
	ecs::entity_t createVisual_ScoreCounter(int posX, int posY, SDL_Color color);
	ecs::entity_t createVisual_PlayerTurnIndicator(int posX, int posY);
	ecs::entity_t createVisual_BackgroundBlackBox(int posX, int posY, float xPixelsSize, float yPixelsSize);

public:

	BoardFactory* boardFactory;
	CardFactory* cardFactory;
	HandFactory* handFactory;
	MatchStateUIFactory* matchStateUIFactory;
};


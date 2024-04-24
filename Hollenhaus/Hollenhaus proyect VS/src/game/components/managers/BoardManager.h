#pragma once
#include "../ComponentUpdate.h"
#include <vector>
#include <list>
#include <functional>
#include "../../Namespaces.h"

#include "IA_manager.h" //intentar cambiarlo para quitarlo de aqui

class Cell;
class Card;
using SDLEventCallback = std::function<void()>;

constexpr int DEFAULT_SIZE = 4;

namespace ecs
{
	class Entity;
	using entity_t = Entity*;
}

class BoardManager : public ComponentUpdate
{
public:
	BoardManager();
	BoardManager(int);
	~BoardManager() override;

	void initComponent() override;
	void update() override;

	bool isFull() const;
	void updateScore();

	/// Setters
	bool setCard(int x, int y, Card* c, Players::Owner o); // true si pudo poner carta (no habia otra ya antes)

	/// Getters
	int getPlayer1Points() const { return pPlayer1; }
	int getPlayer2Points() const { return pPlayer2; }
	Cell* getCell(int x, int y) const;
	std::list<SDLEventCallback> getEffects(Cell* cell) const;

	void setBoard(std::vector<std::vector<ecs::entity_t>>& board)
	{
		_board = board;
		initBoard();

		//llamamos tambien al init board para la IA
		initBoardIA();
	}

	// Setters para las referencias de los elementos visuales
	void setScoreVisualJ1(ecs::entity_t visual) { scoreVisualJ1 = visual; }
	void setScoreVisualJ2(ecs::entity_t visual) { scoreVisualJ2 = visual; }

	// Método para actualizar el aspecto de las referencias visuales del MatchManager
	void updateVisuals();


	//IA
	int heuristicIA(IA_manager::State* s);

	void initBoardIA();

	std::vector<std::vector<bool>> getBoardBoolsIA();
	std::vector<std::vector<Card*>> getBoardCardsIA();
	std::vector<std::vector<Players::Owner>> getBoardOwnerIA();

	//Feedback
	void returnColors();

private:
	void initBoard();
	//cleon: si en la entrega es una constante, os mataré. bueno, yo os mataré
	int size = DEFAULT_SIZE;

	// Un vector de vectores de entidades "Cell".
	std::vector<std::vector<ecs::entity_t>> _board;


	std::vector<std::vector<Cell*>> _boardIA;

	int cardsOnBoard = 0;

	/// match manager
	void applyAllEffects() const;
	int pPlayer1 = 0;
	int pPlayer2 = 0;

	// Referencias a los elementos del HUD
	ecs::entity_t scoreVisualJ1;
	ecs::entity_t scoreVisualJ2;
};

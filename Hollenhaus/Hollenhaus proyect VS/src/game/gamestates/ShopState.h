#pragma once
#include "GameState.h"
#include <vector>


class Factory;

class ShopState : public GameState
{
public: 

	ShopState();	//Constructora

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

	ecs::entity_t createCard(int id, Vector2D pos) override;

	ecs::entity_t createCoin(int x, int y);
	void showCoin(ecs::entity_t coinToShow);
	void makeCoinShine(int cardIndex, ecs::entity_t card, ecs::entity_t shopMngr);
	void updateCoinsOnTable();


private:
	Factory* factory;

	std::vector<int> posX;
	std::vector<int> posY;

	//std::list<ecs::entity_t> coins;
	//Volver a la ciudad
	//Comprar ??
	//Dinero  ??
};


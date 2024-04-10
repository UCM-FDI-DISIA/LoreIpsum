#pragma once
#include "GameState.h"
#include <list>


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
	void updateCoinsOnTable(ecs::entity_t shopMngr);


private:
	Factory* factory;

	//std::list<ecs::entity_t> coins;
	//Volver a la ciudad
	//Comprar ??
	//Dinero  ??
};


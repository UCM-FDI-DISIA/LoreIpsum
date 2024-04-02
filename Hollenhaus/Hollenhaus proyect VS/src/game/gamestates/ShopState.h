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


private:
	Factory* factory;
	int i = GameStateMachine::instance()->getCurrentState()->getMoney();
	int k = 0;
	int index = 0;


	std::list<ecs::entity_t> coins;
	//Volver a la ciudad
	//Comprar ??
	//Dinero  ??
};


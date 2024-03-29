#pragma once
#include "GameState.h"

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

private:
	Factory* factory;

	//Volver a la ciudad
	//Comprar ??
	//Dinero  ??
};


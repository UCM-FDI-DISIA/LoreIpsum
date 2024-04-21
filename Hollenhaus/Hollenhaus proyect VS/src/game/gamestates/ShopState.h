#pragma once
#include "GameState.h"
#include <vector>

const int COIN_VALUE = 100; // Valor de cada moneda.

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

	void cardSelected(int prize) override;
	void deSelected() override;

	void shine(int nCoins);

	ecs::entity_t createCard(int id, Vector2D pos) override;

	ecs::entity_t createCoin(int x, int y);
	void showCoin(ecs::entity_t coinToShow);
	void updateCoinsOnTable();
	void hideCoins();

	void setDecisionManager();


private:
	Factory* factory;

	ecs::entity_t manager;
	//examen ig 3 horas.
	//teoria : esto hace tal eso hace eso, textura hace nsq. relacionado con la infomatica grafica.pipeline, vistas... 30
	//pratica : la practica como base. 70
	// simulacro de examen el dia 8.
	// hace falta aprobar las dos partes para poder aprobar.

	std::vector<int> posX;
	std::vector<int> posY;

	//std::list<ecs::entity_t> coins;
	//Volver a la ciudad
	//Comprar ??
	//Dinero  ??
};


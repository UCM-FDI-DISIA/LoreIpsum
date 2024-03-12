#pragma once
#include "GameState.h"

class ShopState : public GameState
{
public: 

	ShopState();	//Constructora

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

private:
	//Volver a la ciudad
	//Comprar ??
	//Dinero  ??
};


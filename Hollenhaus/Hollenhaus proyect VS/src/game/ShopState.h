#pragma once
#include "GameState.h"

class ShopState : public GameState
{
public: 
	void update() override;
	void render() const override;
	void refresh() override;
	bool onEnter();
	bool onExit();

private:
	//Volver a la ciudad
	//Comprar ??
	//Dinero  ??
};


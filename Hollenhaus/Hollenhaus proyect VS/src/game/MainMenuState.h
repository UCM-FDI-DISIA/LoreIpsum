#pragma once
#include "GameState.h"

class MainMenuState : public GameState
{
	void update() override;
	void render() override;
	void refresh() override;
	bool onEnter();
	bool onExit();

private:

	//Fondo
	//Botones
	//Transicion -> City
	//Salir
};


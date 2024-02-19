#pragma once
#include "GameState.h"

class MainMenuState : public GameState
{
public:

	MainMenuState(Game* game);		//Constructora

	void update() override;
	void render() override;
	void refresh() override;
	void onEnter();
	bool onExit();

private:

	//Fondo
	//Botones
	//Transicion -> City
	//Salir
};


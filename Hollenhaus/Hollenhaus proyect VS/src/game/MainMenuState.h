#pragma once
#include "GameState.h"

class Entity;
class Manager;
class MainMenuState : public GameState
{
public:

	MainMenuState();		//Constructora

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() const override;
	void onExit() const override;

private:

	//Fondo
	//Botones
	//Transicion -> City
	//Salir
};


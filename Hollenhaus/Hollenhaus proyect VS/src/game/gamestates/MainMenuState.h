#pragma once
#include "GameState.h"

class MainMenuState : public GameState
{
public:
	MainMenuState(); //Constructora

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

private:
	ecs::entity_t newGameButton;
	ecs::entity_t multiplayerButton;
	ecs::entity_t exitButton;
	void exitGame();
	//Fondo
	//Botones
	//Transicion -> City
	//Salir
};

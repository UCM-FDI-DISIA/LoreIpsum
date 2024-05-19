#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"

const int TIE_MONEY_GAIN = 50; // Dinero que gana el jugador al empatar.
const int NPC_MONEY_GAIN = 100; // Dinero que gana el jugador al ganar a NPC.
const int TAROT_MONEY_GAIN = 200; // Dinero que gana el jugador al ganar a tarotista.
const int SOULS_GAIN = 1; // Almas que gana el jugador cuando gana a la pitonisa.

class Factory;

class MatchOverState : public GameState
{
public:

	MatchOverState();	// Constructora.
	//MatchOverState(int winner); // Constructora para quitar luego.

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

	// Cambia la ventana en funcion del ganador
	void setWindow(int lastWinner);
	void setJ2(std::string rival) override;

	ecs::entity_t createCard(int id, Vector2D pos) override;

private:
	std::string _background, _text, j2_, _money, _souls;
	int winner;
	Factory* factory;
	bool tarotista;
};
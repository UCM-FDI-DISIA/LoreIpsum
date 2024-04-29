#pragma once
#include "GameState.h"

const int MONEY_GAIN = 300; // Dinero que gana el jugador al ganar.
const int SOULS_GAIN = 1; // Almas que gana el jugador cuando gana a la pitonisa.

class MatchOverState : public GameState
{
public:

	MatchOverState();	// Constructora.

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

	// Cambia la ventana en funcion del ganador.
	void setWindow(int lastWinner);

private:
	std::string _background, _text;
};
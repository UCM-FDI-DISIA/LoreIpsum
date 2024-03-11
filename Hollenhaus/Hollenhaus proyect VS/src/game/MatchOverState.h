#pragma once
#include "GameState.h"
#include "NPC.h"

class MatchOverState : public GameState
{
public:

	MatchOverState();	//Constructora

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

	// cambia la ventana en funcion del ganador
	void setWindow(int lastWinner);

private:
	std::string background, text;
};
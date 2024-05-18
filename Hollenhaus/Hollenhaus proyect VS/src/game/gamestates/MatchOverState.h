#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"

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
	void setJ2(std::string rival) override;

private:
	std::string _background, _text, j2_;
};
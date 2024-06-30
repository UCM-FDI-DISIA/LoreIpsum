#pragma once
//Checkml
#include <game/checkML.h>

#include "GameState.h"
#include <vector>

class SolitaireQuestion : public GameState
{
public:
	// Constructora.
	SolitaireQuestion();

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

};
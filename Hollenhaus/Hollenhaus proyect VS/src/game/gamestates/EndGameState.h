#pragma once
#include "GameState.h"
#include <game/checkML.h>

class EndGameState :
    public GameState
{
public:
	EndGameState();
	~EndGameState();

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;
};


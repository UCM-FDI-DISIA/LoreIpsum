#pragma once
#include "GameState.h"

class MultiplayerGameState
	: public GameState
{
public:
	MultiplayerGameState();
	~MultiplayerGameState() override;

	void refresh() override;
	void update() override;
	void render() const override;


	void onEnter() override;
	void onExit() override;

private:
};

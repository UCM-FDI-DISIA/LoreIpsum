#pragma once

#include "GameState.h"

class MultiplayerModeState : public GameState
{
public:
	MultiplayerModeState();
	~MultiplayerModeState() override;

	void refresh() override;
	void update() override;
	void render() const override;

	void onEnter() override;
	void onExit() override;
};

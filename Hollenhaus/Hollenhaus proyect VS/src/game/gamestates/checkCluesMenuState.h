#pragma once

#include "GameState.h"

class CheckCluesMenuState : public GameState
{
public:
	CheckCluesMenuState();
	~CheckCluesMenuState() override;

	void refresh() override;
	void update() override;
	void render() const override;

	void onEnter() override;
	void onExit() override;
};

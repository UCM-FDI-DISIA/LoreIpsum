#pragma once

#include "GameState.h"

class OptionsMainMenuState : public GameState
{
public:
	OptionsMainMenuState();
	~OptionsMainMenuState() override;

	void refresh() override;
	void update() override;
	void render() const override;

	void onEnter() override;
	void onExit() override;
};

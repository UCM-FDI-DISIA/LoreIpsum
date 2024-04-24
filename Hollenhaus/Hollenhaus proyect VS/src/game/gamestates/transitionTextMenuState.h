#pragma once
#include "GameState.h"

class TransitionTextMenuState : public GameState
{
public:
	TransitionTextMenuState();
	~TransitionTextMenuState() override;

	void refresh() override;
	void update() override;
	void render() const override;

	void onEnter() override;
	void onExit() override;
};

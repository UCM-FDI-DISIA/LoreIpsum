#pragma once
#include "GameState.h"

class PauseMenuState : public GameState
{
public:
	PauseMenuState();
	~PauseMenuState() override;

	void refresh() override;
	void update() override;
	void render() const override;

	void onEnter() override;
	void onExit() override;

	void setPreviousState(int ps)
	{
		previousState = ps;
	}

	int previousState;

private:
	void onDespause();
};

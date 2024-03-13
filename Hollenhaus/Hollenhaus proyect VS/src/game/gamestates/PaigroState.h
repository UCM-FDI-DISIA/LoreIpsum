#pragma once
#include "GameState.h"


class PaigroState : public GameState
{
public:
	PaigroState();

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;
private:

	
};


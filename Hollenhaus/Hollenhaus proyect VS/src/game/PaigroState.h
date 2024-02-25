#pragma once
#include "checkML.h"
#include "GameState.h"

class PaigroState : public GameState
{
public:
	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() const override;
	void onExit() const override;
private:

	
};


#pragma once

#include "GameState.h"

class Factory;

class TutorialState : public GameState
{
public:
	TutorialState();
	~TutorialState() override;

	void refresh() override;
	void update() override;
	void render() const override;

	void onEnter() override;
	void onExit() override;
};

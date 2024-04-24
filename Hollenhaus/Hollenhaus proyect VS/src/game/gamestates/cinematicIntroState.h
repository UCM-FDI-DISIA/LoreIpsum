#pragma once

#include "GameState.h"

class CinematicIntroState : public GameState
{
public:
	CinematicIntroState();
	~CinematicIntroState() override;

	void refresh() override;
	void update() override;
	void render() const override;

	void onEnter() override;
	void onExit() override;
};

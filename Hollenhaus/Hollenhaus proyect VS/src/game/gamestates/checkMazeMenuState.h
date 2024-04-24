#pragma once

#include "GameState.h"

class CheckMazeMenuState : public GameState
{
public:
	CheckMazeMenuState();
	~CheckMazeMenuState() override;

	void refresh() override;
	void update() override;
	void render() const override;

	void onEnter() override;
	void onExit() override;
};

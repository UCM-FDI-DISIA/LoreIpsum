#pragma once
#include "GameState.h"

class TextComponent;

class MultiplayerPreGameState
	: public GameState
{
public:
	MultiplayerPreGameState();
	~MultiplayerPreGameState() override;


	void refresh() override;
	void update() override;
	void render() const override;


	void onEnter() override;
	void onExit() override;

private:
	// TextComponent* tc;
};

#pragma once
#include "GameState.h"

class MultiplayerLobbyState
	: public GameState
{
public:
	MultiplayerLobbyState();
	~MultiplayerLobbyState() override;


	void refresh() override;
	void update() override;
	void render() const override;


	void onEnter() override;
	void onExit() override;

private:
};

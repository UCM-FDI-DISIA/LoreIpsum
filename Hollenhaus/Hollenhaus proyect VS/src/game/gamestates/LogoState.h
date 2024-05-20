#pragma once
//Checkml
#include <game/checkML.h>
#include "GameState.h"
class LogoState :
    public GameState
{
public:
    LogoState();
	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

private:
	ecs::entity_t logo_;

	Uint32 time_;
	Uint32 currentTime_;
};


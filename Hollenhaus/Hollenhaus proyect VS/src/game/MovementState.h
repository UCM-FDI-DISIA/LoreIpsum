#pragma once
#include "checkML.h"
#include "GameState.h"
#include "NPC.h"
#include "Entity.h"
#include "Manager.h"

class MovementState : public GameState
{
public:
	MovementState();

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() const override;
	void onExit() const override;

private:
	float scrollSpeed = 1.0f;
};


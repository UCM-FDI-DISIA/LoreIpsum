#pragma once
#include "checkML.h"
#include "GameState.h"
#include "NPC.h"
#include "Entity.h"

class Manager;
class PaigroState : public GameState
{
public:
	PaigroState();

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() const override;
	void onExit() const override;
private:

	
};


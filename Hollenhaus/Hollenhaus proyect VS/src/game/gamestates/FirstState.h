#pragma once
//Checkml
#include <game/checkML.h>
#include "GameState.h"
class FirstState :
    public GameState
{
public:
	FirstState();
	~FirstState() override;
	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;
};


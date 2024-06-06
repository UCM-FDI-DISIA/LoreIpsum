#pragma once
//Checkml
#include <game/checkML.h>

#include "GameState.h"
#include <vector>
class Factory;

class CasinoState : public GameState
{
public:
	// Constructora.
	CasinoState();

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;



private:
	
	Factory* factory;

};
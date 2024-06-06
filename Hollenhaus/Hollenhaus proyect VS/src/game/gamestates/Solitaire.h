#pragma once
//Checkml
#include <game/checkML.h>

#include "GameState.h"
#include <vector>
class Factory;

class Solitaire : public GameState
{
public:
	// Constructora.
	Solitaire();

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;



private:

	Factory* factory;

};

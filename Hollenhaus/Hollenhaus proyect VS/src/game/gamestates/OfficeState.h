#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"

class Factory;

class OfficeState : public GameState
{
public:

	OfficeState();		//Constructora
	~OfficeState() { }
	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

	void onPauseOF();

private:
	Factory* factory;

	//Cambiar a combate (Tarotista) -> Tel�fono
	//Gestionar mazo
	//Volver a CIU
};


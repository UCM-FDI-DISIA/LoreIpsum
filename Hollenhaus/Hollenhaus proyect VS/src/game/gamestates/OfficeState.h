#pragma once

#include "GameState.h"

class Factory;

class OfficeState : public GameState
{
public:
	OfficeState(); //Constructora

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

private:
	Factory* factory;

	//Cambiar a combate (Tarotista) -> Teléfono
	//Gestionar mazo
	//Volver a CIU
};

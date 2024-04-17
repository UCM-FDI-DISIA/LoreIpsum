#pragma once

#include "GameState.h"

class OfficeState : public GameState
{
public:

	OfficeState();		//Constructora

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

	void onPauseOF();

private:

	//Cambiar a combate (Tarotista) -> Teléfono
	//Gestionar mazo
	//Volver a CIU
};


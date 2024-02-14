#pragma once
#include "GameState.h"

class OfficeState : public GameState
{
public:
	void update() override;
	void render() override;
	void refresh() override;
	bool onEnter();
	bool onExit();
private:

	//Cambiar a combate (Tarotista) -> Teléfono
	//Gestionar mazo
	//Volver a CIU
};


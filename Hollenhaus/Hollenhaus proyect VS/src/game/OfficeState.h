#pragma once
#include "GameState.h"
#include  "Entity.h"
#include "NPC.h"
class OfficeState : public GameState
{
public:

	OfficeState();		//Constructora

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;
private:

	//Cambiar a combate (Tarotista) -> Teléfono
	//Gestionar mazo
	//Volver a CIU
};


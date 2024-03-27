#pragma once

#include "GameState.h"

class DeckBuildingState : public GameState
{
public:

	DeckBuildingState();		//Constructora

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


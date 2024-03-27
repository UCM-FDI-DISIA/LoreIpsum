#pragma once

#include "GameState.h"
#include "../components/Card.h"
#include "../components/managers/PizarraManager.h"
#include "../components/managers/DrawerManager.h"

class DeckBuildingState : public GameState
{
public:

	DeckBuildingState();		//Constructora

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

	void moveToPizarra(Card* card);
	void moveToDrawer(Card* card);
private:
	PizarraManager* pizarra;
	DrawerManager* drawer;
	//Cambiar a combate (Tarotista) -> Teléfono
	//Gestionar mazo
	//Volver a CIU
};


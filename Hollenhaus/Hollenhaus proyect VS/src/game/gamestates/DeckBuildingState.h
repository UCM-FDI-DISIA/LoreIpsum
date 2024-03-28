#pragma once

#include "GameState.h"
class Card;
class PizarraManager;
class DrawerManager;

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
	PizarraManager* pizarra_;
	DrawerManager* drawer_;
	//Cambiar a combate (Tarotista) -> Teléfono
	//Gestionar mazo
	//Volver a CIU
};


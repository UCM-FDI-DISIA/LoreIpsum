#pragma once

#include "GameState.h"
class Card;
class PizarraManager;
class DrawerManager;
class Factory;

class DeckBuildingState : public GameState
{
public:

	DeckBuildingState(); // Constructora

	// heredados basicos
	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

	// Deckbuilding
	void moveToPizarra(Card* card);
	void moveToDrawer(Card* card);

	ecs::entity_t createCard(int id, Vector2D pos) override;

private:

	Factory* factory;

	// variables privadas de cajon y pizarra
	PizarraManager* pizarra_;
	DrawerManager* drawer_;
};
#pragma once

#include "GameState.h"
class Card;
class PizarraManager;
class DrawerManager;
class Factory;
class TextComponent;

class DeckBuildingState : public GameState
{
public:

	DeckBuildingState();		//Constructora

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

	void onPauseDB();

	void moveToPizarra(Card* card);
	void moveToDrawer(Card* card);

	ecs::entity_t createCard(int id, Vector2D pos) override;

private:
	ecs::entity_t rice;
	PizarraManager* pizarra_;
	DrawerManager* drawer_;
	TextComponent* cantCards_;
	Factory* factory;

	bool paused;
};
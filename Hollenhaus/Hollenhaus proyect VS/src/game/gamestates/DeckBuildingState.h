#pragma once

//Checkml
#include <game/checkML.h>

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
	DeckBuildingState(bool t);		//Constructora


	~DeckBuildingState() { }
	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

	void onPauseDB();

	void moveToPizarra(Card* card);
	void moveToDrawer(Card* card);

	ecs::entity_t createCard(int id, Vector2D pos) override;



	// -------------- tutorial --------------------
	void setTutorial();
	void prepareTutorial();
	void startTutorial(bool a);

private:
	ecs::entity_t rice;
	PizarraManager* pizarra_;
	DrawerManager* drawer_;
	TextComponent* cantCards_;
	Factory* factory;

	ecs::entity_t fbSaved;
	tweeny::tween<int> tweenFade;
	int fbTimer = 0;
	bool paused;
	bool isTutorial = false;

	ecs::entity_t base;             // entidad para colocar los popups, se va moviendo segun donde los queramos
	ecs::entity_t tutorial;

	void resetFade();
};
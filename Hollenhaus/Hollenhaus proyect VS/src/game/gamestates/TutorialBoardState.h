#pragma once
#include "GameState.h"

class Factory;
class TutorialManager;

class TutorialBoardState :
	public GameState
{
public:
	TutorialBoardState();
	~TutorialBoardState() override;


	void refresh() override;
	void update() override;
	void render() const override;

	void onEnter() override;
	void onExit() override;

private:
	//
	void setBoard();
	void setBaseEntity();
	void initTutorial();

	Factory* factory; //
	ecs::entity_t base; // entidad para colocar los popups, se va moviendo segun donde los queramos
	ecs::entity_t tutorial;
	ecs::entity_t colliderWallBase;

	//TutorialBoardManager* tutorialManager_;

	std::vector<ecs::entity_t> objs;

	int cooldown = 10;
	int count = 0;
};

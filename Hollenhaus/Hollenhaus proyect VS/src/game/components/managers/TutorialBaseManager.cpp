#include "..\pchs\pch.h"
#include "TutorialBaseManager.h"

#include <SDL.h>
#include "../../components/Drag.h"
#include "../../components/managers/CardStateManager.h"
#include "../../components/managers/DragManager.h"
#include "../../components/managers/Manager.h"
#include "../../../sdlutils/InputHandler.h"
#include "../../factories/Factory.h"
#include "../../factories/DialogueFactory_V0.h"
#include "../../factories/CardFactory_v0.h"
#include "../../factories/CardFactory_v1.h"
#include "../../factories/BoardFactory_v0.h"
#include "../../factories/MatchStateUIFactory_v0.h"
#include "../../components/managers/MatchManager.h"
#include "../../components/managers/BoardManager.h"
#include "../../components/basics/TextComponent.h"
#include "../../components/managers/MatchManager.h"
#include "../../components/EndTurnButton.h"
#include "../../components/NPC.h"

#include "../../components/managers/IA_manager.h"

#include "../../components/managers/Manager.h"
#include "../../GameStateMachine.h"
#include "../../components/managers/PlayerCardsManager.h"
#include "../../TutorialManager.h"

TutorialBaseManager::TutorialBaseManager()
{
}

TutorialBaseManager::TutorialBaseManager(ecs::entity_t b, ecs::entity_t t) 
{
	base = b;
	tutorial = t;
}

TutorialBaseManager::~TutorialBaseManager()
{
}

void TutorialBaseManager::initComponent()
{

}

void TutorialBaseManager::update()
{
	if (actionEnded()) {

		nextTutorialState();

		resetEnded();
	}

	updateTutorialState();
}

void TutorialBaseManager::nextTutorialState()
{
	if (!checked) {
		nextState = tutorial->getComponent<TutorialManager>()->nextState();

		checked = true;
	}
}

void TutorialBaseManager::updateTutorialState()
{
	if (currentState != nextState) {
		ent_->getComponent<TutorialManager>()->wait([this]
			{
				setState(); });
	}
}

bool TutorialBaseManager::actionEnded()
{
	return ent_->getComponent<TutorialManager>()->hasEnded();

}

void TutorialBaseManager::resetEnded()
{
	ent_->getComponent<TutorialManager>()->resetAction();

}

void TutorialBaseManager::setState()
{

}

ecs::entity_t TutorialBaseManager::createPopUp(float x, float y, std::string popup, int convo)
{
	JsonData::DialogueData dialogue = sdlutils().dialogues().at(popup);

	int node = 0;

	factory;

	base;

	// crear dialogo del FACTORY de dialogos
	//// Mirar comentario en el interior de la función
	ecs::entity_t pop = factory->createDialogue(dialogue.NPCName(), convo, node,
		{ x, y },//POS
		{ 0.25, 0.25 }, //SIZE (poli: no cambia nada?¿)	// Luis: Dentro de createDialogue, size depende del tamaó del sprite, y no es parametrizable
		2, 10, base,
		200, dialogue.Convo(convo).isAuto(),  //LAYER
		"8bit_size_20",	//mirar el JSON para cambiar el tamanio de texto
		SDL_Color({ 0, 0, 0, 255 }),
		220, //wrap length
		Text::BoxPivotPoint::LeftTop,
		Text::TextAlignment::Left);

	return pop;
}

ecs::entity_t TutorialBaseManager::createPopUp(float x, float y, std::string popup, int convo, ecs::entity_t b)
{
	JsonData::DialogueData dialogue = sdlutils().dialogues().at(popup);

	int node = 0;

	factory;

	base;

	// crear dialogo del FACTORY de dialogos
	//// Mirar comentario en el interior de la función
	ecs::entity_t pop = factory->createDialogue(dialogue.NPCName(), convo, node,
		{ x, y },//POS
		{ 0.25, 0.25 }, //SIZE (poli: no cambia nada?¿)	// Luis: Dentro de createDialogue, size depende del tamaó del sprite, y no es parametrizable
		5, 10, b,
		200, dialogue.Convo(convo).isAuto(),  //LAYER
		"8bit_size_20",	//mirar el JSON para cambiar el tamanio de texto
		SDL_Color({ 0, 0, 0, 255 }),
		220, //wrap length
		Text::BoxPivotPoint::LeftTop,
		Text::TextAlignment::Left);

	return pop;
}

void TutorialBaseManager::setBase(ecs::entity_t b)
{
	base = b;
}

void TutorialBaseManager::setTutorial(ecs::entity_t t)
{
	tutorial = t;

}

void TutorialBaseManager::setObjs(std::vector<ecs::entity_t> v)
{
	objs = v;

	setLayers(v);
}

void TutorialBaseManager::setLayers(std::vector<ecs::entity_t> v)
{
	tutorial->getComponent<TutorialManager>()->setLayers(objs);

}

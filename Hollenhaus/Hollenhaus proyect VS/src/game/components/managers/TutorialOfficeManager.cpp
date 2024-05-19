#include "..\pchs\pch.h"
#include "TutorialOfficeManager.h"

#include "../../TutorialManager.h"
#include "TutorialBaseManager.h"
#include "../../factories/DialogueFactory_V0.h"
#include "../../factories/Factory.h"


TutorialOfficeManager::TutorialOfficeManager(ecs::entity_t b, ecs::entity_t t)
	: TutorialBaseManager(b, t)
{
}

TutorialOfficeManager::~TutorialOfficeManager()
{
	delete factory;
	factory = nullptr;
}

void TutorialOfficeManager::initComponent()
{
	factory = new Factory();
	factory->SetFactories(
		static_cast<DialogueFactory*>(new DialogueFactory_V0())
	);

	currentState = Tutorials::Oficina::OFFICE_NONE;
	nextState = Tutorials::Oficina::OFFICE_INIT;
	ended = false;
	checked = false;

}

void TutorialOfficeManager::update()
{
	if (actionEnded()) {

		nextTutorialState();

		resetEnded();
	}

	updateTutorialState();
}

void TutorialOfficeManager::setState()
{
	int t = ent_->getComponent<TutorialManager>()->getNextState();
	ent_->getComponent<TutorialManager>()->activateColliders(objs);
	//ent_->getComponent<TutorialManager>()->resetColliderWall(objs);

	switch (t)
	{
	case Tutorials::Oficina::OFFICE_INIT:
		setINIT();
		break;
	case Tutorials::Oficina::OFFICE_PHONE:
		setPHONE();
		break;
	case Tutorials::Oficina::OFFICE_PIZARRA:
		setPIZARRA();
		break;
	default:
		break;
	}

	currentState = nextState;

	ent_->getComponent<TutorialManager>()->setCurrentTutorialState(t);

	checked = false;


}

void TutorialOfficeManager::setINIT()
{
	createPopUp(250, 250, "Office Tutorial", 0, base);
	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);

}

void TutorialOfficeManager::setPHONE()
{
	createPopUp(100, 250, "Office Tutorial", 1, base);
	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);

}

void TutorialOfficeManager::setPIZARRA()
{
	createPopUp(200, 50, "Office Tutorial", 2, base);
	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);

}

#include <../pchs/pch.h>

#include "DialogueEventCollection.h"
#include "../factories/Factory.h"
#include "../factories/DecisionFactory_V0.h"
#include "../TutorialManager.h"
#include "../components/managers/TutorialBoardManager.h"
#include "../components/Button.h"

DialogueEventCollection::DialogueEventCollection()
{
	
}

void DialogueEventCollection::ChangeScene(int scene)
{
	std::cout << "Change to: " << scene << std::endl;
	GameStateMachine::instance()->setState(scene);
}

void DialogueEventCollection::ConfirmationPopUp(ecs::entity_t parent, int greenDecision, int redDecision, int scene)
{
	Factory * factory = new Factory();
	factory->SetFactories(
		static_cast<DecisionFactory*>(new DecisionFactory_V0())
	);

	float x = parent->getComponent<Transform>()->getGlobalPos().getX();
	float y = parent->getComponent<Transform>()->getGlobalPos().getY() + 150;

	factory->createDecision({ x,y }, //pos
							{ 0,0 }, //size
							parent, //parent
							4, //layer
							scene, // Escena
							greenDecision, //greenDecision
							redDecision, //redDecision
							Fonts::GROTESK_24, //fontId
							Colors::MIDNIGHT_HOLLENHAUS, //color del txt
							100, //wraplength
							Text::BoxPivotPoint::LeftTop,
							Text::TextAlignment::Center);

	//auto a = parent->hasComponent<BoxCollider>();

	auto coll = parent->getComponent<NextText>()->getCollider();
	coll->setPosOffset({ 1000, 1000});

	delete factory;
	factory = nullptr;
}

void DialogueEventCollection::ActionEnded()
{
	// handler del tutorial para tocar el action done
	ecs::entity_t ent = GameStateMachine::instance()->getMngr()->getHandler(ecs::hdlr::TUTORIAL_MANAGER);
	ent->getComponent<TutorialManager>()->actionEnded();

	// TUTORIAL BOARD MANAGER REF
}

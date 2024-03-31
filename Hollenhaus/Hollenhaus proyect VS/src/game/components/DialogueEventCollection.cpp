#include "pch.h"
#include "DialogueEventCollection.h"
#include "../factories/Factory.h"
#include "../factories/DecisionFactory_V0.h"

DialogueEventCollection::DialogueEventCollection()
{
	
}

void DialogueEventCollection::ChangeScene(int scene)
{
	std::cout << "Change to: " << scene << std::endl;
	GameStateMachine::instance()->setState(scene);
}

void DialogueEventCollection::ConfirmationPopUp(ecs::entity_t parent) //poli
{
	Factory * factory = new Factory();
	factory->SetFactories(
		static_cast<DecisionFactory*>(new DecisionFactory_V0())
	);
	factory->createDecision({ 0,0 }, //pos
		{ 100,100 }, //size
		parent, //parent
		4, //layer
		"8bit_size_12", //fontId
		SDL_Color({ 0, 0, 0, 255 }), //color del txt
		15, //wraplength
		Text::BoxPivotPoint::LeftTop,
		Text::TextAlignment::Center);

	delete factory;
	factory = nullptr;
}

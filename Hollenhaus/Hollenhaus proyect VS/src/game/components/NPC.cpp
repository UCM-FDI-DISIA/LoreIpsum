#include "pch.h"
#include "NPC.h"
#include "managers/Manager.h"
#include "basics/BoxCollider.h"
#include "TypeWriter.h"
#include "../factories/Factory.h"
#include "../factories/DialogueFactory_V0.h"
#include "../factories/CardFactory_v1.h"


NPC::NPC(int scene)
{
	_scene = scene;
	click = false;
	myBoxCollider = nullptr;
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(_scene); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
	type = 0;


	factory = new Factory();
	factory->SetFactories(
		static_cast<DialogueFactory*>(new DialogueFactory_V0())
	);

}

NPC::NPC(int scene, int t)
{
	_scene = scene;
	click = false;
	myBoxCollider = nullptr;
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(_scene); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
	type = t;

	factory = new Factory();
	factory->SetFactories(
		static_cast<DialogueFactory*>(new DialogueFactory_V0())
	);


}

NPC::~NPC() {
	ih().clearFunction(InputHandler::MOUSE_LEFT_CLICK_DOWN, [this] {OnLeftClickDown(_scene); });
	ih().clearFunction(InputHandler::MOUSE_LEFT_CLICK_UP, [this] {OnLeftClickUp(); });

	//delete factory;
	//factory = nullptr;
}

void NPC::initComponent(){
	myBoxCollider = mngr_->getComponent<BoxCollider>(ent_);
}

void NPC::OnLeftClickDown(int scene) {
	myBoxCollider;
	reactToClick(scene);
	click = true;
}
void NPC::OnLeftClickUp() {
	click = false; // Resetea el click al soltar para que se pueda volver a pulsar.
}

void NPC::reactToClick(int scene) // Te lleva al estado que le mandes.
{
	if (!click && myBoxCollider->isCursorOver()) {

		if (type == 0) {
			TuVieja("Cambio de escena.");
			GameStateMachine::instance()->setState(scene);
		}
		else if (type == 1) {
			talkTo();
		}
		
	}
}

void NPC::talkTo()
{
	if (!click && myBoxCollider->isCursorOver()) {
		TuVieja("Que charlatan el tio...");
		
		float x = ent_->getComponent<Transform>()->getGlobalPos().getX();
		float y = ent_->getComponent<Transform>()->getGlobalPos().getY();

		TuVieja(std::to_string(x));

		// crear dialogo del FACTORY de dialogos
		factory->createDialogue("El Xungo del Barrio", 0, 0, {x,y}, {10,10},
			5, 10, getEntity(), "8bit_size_12", SDL_Color({255, 255, 255, 255}), 100, Text::BoxPivotPoint::CenterCenter,
			Text::TextAlignment::Center);
	}

}

void NPC::update() {

}
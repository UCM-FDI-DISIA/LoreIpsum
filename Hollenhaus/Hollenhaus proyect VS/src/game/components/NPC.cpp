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
	talking = false;
	_id = 0;


	factory = new Factory();
	factory->SetFactories(
		static_cast<DialogueFactory*>(new DialogueFactory_V0())
	);

}

NPC::NPC(int scene, std::string name_)
{
	_scene = scene;
	click = false;
	myBoxCollider = nullptr;
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(_scene); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
	type = 0;
	talking = false;
	name = name;


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
	talking = false;

	factory = new Factory();
	factory->SetFactories(
		static_cast<DialogueFactory*>(new DialogueFactory_V0())
	);

}

NPC::NPC(int scene, int t, std::string name_)
{
	_scene = scene;
	click = false;
	myBoxCollider = nullptr;
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(_scene); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
	type = t;
	talking = false;
	name = name_;

	factory = new Factory();
	factory->SetFactories(
		static_cast<DialogueFactory*>(new DialogueFactory_V0())
	);


}

NPC::~NPC() {
	ih().clearFunction(InputHandler::MOUSE_LEFT_CLICK_DOWN, [this] {OnLeftClickDown(_scene); });
	ih().clearFunction(InputHandler::MOUSE_LEFT_CLICK_UP, [this] {OnLeftClickUp(); });

	delete factory;
	factory = nullptr;
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
	if (!click && myBoxCollider->isCursorOver() && !talking) {
		TuVieja("Que charlatan el tio...");
		
		float x = ent_->getComponent<Transform>()->getGlobalPos().getX() - 150;
		float y = ent_->getComponent<Transform>()->getGlobalPos().getY() - 250;

		TuVieja(std::to_string(x));

		JsonData::DialogueData dialogue = sdlutils().dialogues().at(name);
		int conv = 0;
		int node = 0;

		// crear dialogo del FACTORY de dialogos
		factory->createDialogue(dialogue.NPCName(), conv, node,
								{x,y}, //POS
								{100,100}, //SIZE (poli: no cambia nada?¿)
								5, 10, getEntity(), 
								3, dialogue.Convo(conv).isAuto(),  //LAYER
								"8bit_size_20",	//mirar el JSON para cambiar el tamanio de texto
								SDL_Color({0, 0, 0, 255}), 
								150, //wrap length
								Text::BoxPivotPoint::LeftTop, //lo de pivot no me deja centrar el texto con el cuadrado-> preguntar a Parres uwu
								Text::TextAlignment::Center);

		talking = true;
	}

}

void NPC::stoppedTalking()
{
	talking = false;
}

void NPC::update() {

}
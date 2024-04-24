#include <../pchs/pch.h>

#include "NPC.h"
#include "managers/Manager.h"
#include "basics/BoxCollider.h"
#include "TypeWriter.h"
#include "../factories/Factory.h"
#include "../factories/DialogueFactory_V0.h"
#include "../factories/CardFactory_v1.h"
#include "../components/NextText.h"
#include "../components/DialogueBoxDestroyer.h"

NPC::NPC(int scene, int t, std::string name_, bool toFadeIn, bool toFadeOut)
: _scene(scene), click(false), type(t), talking(false), name(name_), myBoxCollider(nullptr)
{
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this, toFadeIn, toFadeOut] { OnLeftClickDown(_scene, toFadeIn, toFadeOut); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });

	factory = new Factory();
	factory->SetFactories(
		static_cast<DialogueFactory*>(new DialogueFactory_V0())
	);
}

NPC::~NPC()
{
	ih().clearFunction(InputHandler::MOUSE_LEFT_CLICK_DOWN, [this] {OnLeftClickDown(_scene); });
	ih().clearFunction(InputHandler::MOUSE_LEFT_CLICK_UP, [this] {OnLeftClickUp(); });

	delete factory;
	factory = nullptr;
}

void NPC::initComponent()
{
	myBoxCollider = mngr_->getComponent<BoxCollider>(ent_);
	myTransform = mngr_->getComponent<Transform>(ent_);
}

void NPC::OnLeftClickDown(int scene, bool toFadeIn, bool toFadeOut) 
{
	myBoxCollider;
	reactToClick(scene, toFadeIn, toFadeOut);
	click = true;
}

void NPC::OnLeftClickUp() 
{
	click = false; // Resetea el click al soltar para que se pueda volver a pulsar.
}

void NPC::reactToClick(int scene, bool toFadeIn, bool toFadeOut) // Te lleva al estado que le mandes.
{
	// Recoge la posicion X del NPC y determina si esta cerca de Paul (se usa luego en talkTo).
	pos = myTransform->getGlobalPos().getX();
	closeToPaul = pos > 200 && pos < sdlutils().width() - 200;

	if (!click && myBoxCollider->isCursorOver()) // Recoge click para el cambio de escena.
	{
		if (type == BUTTON) {
			TuVieja("Cambio de escena.");
			GameStateMachine::instance()->setState(scene, toFadeIn, toFadeOut);
		}
		else if (type == TALKING) 
		{
			talkTo();
		}
	}
}

void NPC::talkTo()
{
	if (!click && myBoxCollider->isCursorOver() && !talking && closeToPaul) // Recoge click para hablar con un NPC.
	{
		TuVieja("Que charlatan el tio...");

		float x = ent_->getComponent<Transform>()->getGlobalPos().getX() - 150;
		float y = ent_->getComponent<Transform>()->getGlobalPos().getY() - 250;

		TuVieja(std::to_string(x));

		JsonData::DialogueData dialogue = sdlutils().dialogues().at(name);
		int conv = 0;
		int node = 0;

		// crear dialogo del FACTORY de dialogos
		//// Mirar comentario en el interior de la funcion
		npcDialogue = factory->createDialogue(dialogue.NPCName(), conv, node,
								{x, y},//POS
								{2,2}, //SIZE
								5, //Speed
								10, //Cooldown
								getEntity(), //Parent 
								3, //LAYER
								dialogue.Convo(conv).isAuto(), //Si el texto es auto o no
								"8bit_size_20",	//mirar el JSON resources para cambiar el tamanio de texto
								SDL_Color({0, 0, 0, 255}), //Color black
								220, //wrap length
								Text::BoxPivotPoint::LeftTop,
								Text::TextAlignment::Left);
		talking = true;
	}
}

void NPC::stoppedTalking()
{
	talking = false;
}

void NPC::update()
{
	// Si el dialogo ha sido creado y no estamos cerca de Paul -> destruir dialog, y dejamos de hablar.
	if (talking && !closeToPaul)
	{
		npcDialogue->getComponent<DialogueBoxDestroyer>()->destroy();
		talking = false;
	}
}
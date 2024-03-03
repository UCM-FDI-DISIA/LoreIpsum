#include "NPC.h"
#include "Entity.h"
#include "Manager.h"

NPC::NPC(int scene)
{
	_scene = scene;
	click = false;
	myBoxCollider = nullptr;
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(_scene); });
}

NPC::~NPC() {
	ih().clearFunction(InputHandler::MOUSE_LEFT_CLICK_DOWN, [this] {OnLeftClickDown(_scene); });
}
void NPC::initComponent()
{
	myBoxCollider = mngr_->getComponent<BoxCollider>(ent_);
	
}
void NPC::OnLeftClickDown(int scene) {
	
	myBoxCollider;
	reactToClick(scene);
	click = true;

}

void NPC::reactToClick(int scene) // Te lleva al estado que le mandes.
{
	if (!click && myBoxCollider->isCursorOver()) {

		TuVieja("Cambio de escena.");
		GameStateMachine::instance()->setState(scene);
	}
}
void NPC::update() {

}
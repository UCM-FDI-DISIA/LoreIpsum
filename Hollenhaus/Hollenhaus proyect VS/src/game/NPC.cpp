#include "NPC.h"
#include "Entity.h"
#include "Manager.h"

NPC::NPC()
{
	
}

NPC::~NPC() {

}
void NPC::initComponent()
{
	myBoxCollider = mngr_->getComponent<BoxCollider>(ent_);

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUP(); });
	click = false;
}
void NPC::OnLeftClickDown() {
	
	click = true;
	reactToClick();

}
void NPC::OnLeftClickUP()
{
	click = false;
}
void NPC::reactToClick()
{
	if (click && myBoxCollider->isCursorOver()) {
		TuVieja("Cambio de escena.");
		GameStateMachine::instance()->setState(5); // Demomento pasa de CityState a PaigroState que es el 5 (creo).
	}
}
void NPC::update() {

}
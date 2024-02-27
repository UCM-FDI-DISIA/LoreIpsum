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
	
}
void NPC::OnLeftClickDown() {
	Vector2D mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);

	if (myBoxCollider->isCursorOver()) {
		
		GameStateMachine::instance()->setState(6); // Demomento pasa de CityState a PaigroState que es el 5 (creo).
		
	}
	TuVieja("Cambio de escena");
}
void NPC::update() {

}
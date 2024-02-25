#include "NPC.h"
#include "Entity.h"

NPC::NPC() :myBoxCollider() {

}
NPC::~NPC() {
	
}
void NPC::initComponent() {
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	myBoxCollider = ent_->getComponent<BoxCollider>();
}
void NPC::OnLeftClickDown() {
	Vector2D mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);

	if (myBoxCollider->isCursorOver()) {
		GameStateMachine().setState(5); // Demomento pasa de CityState a PaigroState que es el 5 (creo).
	}
}
void NPC::update() {

}
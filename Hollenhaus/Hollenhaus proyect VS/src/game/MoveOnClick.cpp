#include "MoveOnClick.h"
#include "Entity.h"
#include "Manager.h"
#include "../sdlutils/SDLUtils.h"


MoveOnClick::MoveOnClick() : movement(scrollSpeed,0)
{
}

MoveOnClick::~MoveOnClick()
{
}

void MoveOnClick::initComponent()
{
	myBoxCollider = ent_->getComponent<BoxCollider>();
	myTransform = ent_->getComponent<Transform>();
	
	move = false;

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	
}

void MoveOnClick::update()
{
	if (move) {

		//queremos que el vector movement vaya actualizando su X para se vea un movimiento fluido
		scrollSpeed--;
		movement.setX(scrollSpeed);

		myTransform->setGlobalPos(movement);
		
		float halfScreen = sdlutils().width() / 2.0f;

		!move;
	}
}

void MoveOnClick::OnLeftClickDown()
{
	mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);
	myPos = myTransform->getGlobalPos();

	if (myBoxCollider->isCursorOver())
	{
		move = true;
	}
}

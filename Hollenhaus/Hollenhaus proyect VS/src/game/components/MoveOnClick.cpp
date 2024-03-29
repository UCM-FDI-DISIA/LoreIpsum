#include "pch.h"
#include "MoveOnClick.h"
#include "../Entity.h"
#include "managers/Manager.h"


MoveOnClick::MoveOnClick()
{
}

MoveOnClick::~MoveOnClick()
{
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	
}

void MoveOnClick::initComponent()
{
	myBoxCollider = ent_->getComponent<BoxCollider>();
	myTransform = ent_->getComponent<Transform>();
	
	move = false;
	movement.setX(myTransform->getGlobalPos().getX());

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	
}

void MoveOnClick::update()
{
	//parar cuando se centre
	if (movement.getX() == moveTo)
	{
		move = false;
	}
	// parar cuando llegue a los límites de la ciudad por la derecha y se pulse en la derecha
	else if (movement.getX() >= 0 && mousePos.getX() < halfScreen) 
	{
		move = false;
	}
	// parar cuando llegue a los límites de la ciudad por la izquierda y se pulse en la izquierda
	else if (movement.getX() <= -2049 && mousePos.getX() >= halfScreen) 
	{
		move = false;
	}
	else if (move) 
	{
		if (mousePos.getX() >= halfScreen)
		{
			scrollSpeed--;
		}
		else if (mousePos.getX() < halfScreen)
		{
			scrollSpeed++;
		}
		movement.setX(myPos.getX() + scrollSpeed);
		myTransform->setGlobalPos(movement);
	}
}

void MoveOnClick::OnLeftClickDown()
{
	mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);
	myPos = myTransform->getGlobalPos();

	//Si pulsamos en el collider, efectuamos el movimiento
	if (myBoxCollider->isCursorOver() && mouseRaycast() == ent_) {
		move = true;
		scrollSpeed = 1.0f;

		moveTo = myTransform->getGlobalPos().getX() - (mousePos.getX() - halfScreen);
	}
}

void MoveOnClick::StopMoving()
{
	move = false;
}

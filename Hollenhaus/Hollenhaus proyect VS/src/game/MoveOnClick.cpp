#include "MoveOnClick.h"
#include "Entity.h"
#include "Manager.h"


MoveOnClick::MoveOnClick()
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
	if (move)
	{
		//float a = mousePos.getX() - halfScreen;
		//posx = posx - a;
		if (mousePos.getX() >= halfScreen)
		{
			scrollSpeed--;
			movement.setX(myPos.getX() + scrollSpeed);
		}
		else if (mousePos.getX() < halfScreen)
		{
			scrollSpeed++;
			movement.setX(myPos.getX() + scrollSpeed);
		}

		myTransform->setGlobalPos(movement);

		if(myPos.getX() == myPos.getX() - halfScreen) //condicion que no va?¿¿?¿?¿?¿ ayuda
		{
			move = false;
		}
	}
}

void MoveOnClick::OnLeftClickDown()
{
	mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);
	myPos = myTransform->getGlobalPos();

	//Si pulsamos en el collider, efectuamos el movimiento
	if (myBoxCollider->isCursorOver()){
		move = true;
		scrollSpeed = 1.0f;
	}
}

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
		if (mousePos.getX() > halfScreen)
		{
			scrollSpeed--;
		}
		else if(mousePos.getX() < halfScreen)
		{
			scrollSpeed++;
		}

		movement.setX(myPos.getX() + scrollSpeed);
		myTransform->setGlobalPos(movement);
		
		//condicion que falta sacar
		/*if () {
			move = false;
		}*/
	}
}

void MoveOnClick::OnLeftClickDown()
{
	mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);
	myPos = myTransform->getGlobalPos();

	//Si pulsamos en el collider, efectuamos el movimiento
	if (myBoxCollider->isCursorOver()){
		std::cout << mousePos.getX() << std::endl;
		//std::cout << myPos.getX() << std::endl;
		move = true;
	}
}

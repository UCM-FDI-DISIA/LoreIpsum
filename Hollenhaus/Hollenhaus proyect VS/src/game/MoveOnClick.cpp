#include "MoveOnClick.h"
#include "Entity.h"
#include "Manager.h"


MoveOnClick::MoveOnClick() : movement(0,0)
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


	if(move) {

		if (mousePos.getX() > halfScreen) {
			//el fondo se movera de derecha a izquierda
			scrollSpeed--;
			std::cout << mousePos.getX() << std::endl;
			//if (myPos.getX() == mousePos.getX() - halfScreen)
			//{
			//	move = false;
			//}
		}
		else {
			//el fondo se movera de izquierda a derecha
			scrollSpeed++;
		}

		movement.setX(scrollSpeed);
		myTransform->setGlobalPos(movement);
		
		move = false;

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

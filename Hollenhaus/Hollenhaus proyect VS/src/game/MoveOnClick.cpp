#include "MoveOnClick.h"
#include "Entity.h"
#include "Manager.h"


MoveOnClick::MoveOnClick() : transformer(0)
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
	if (move == true) {
		std::cout << myPos.getX() << std::endl;
		myPos.set(transformer, 0);
		//myTransform.set que esta en otra rama xd
		std::cout << myPos.getX() << std::endl;


		move = false;
	}
}

void MoveOnClick::OnLeftClickDown()
{
	mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);
	myPos = myTransform->getGlobalPos();
	transformer += 100.0f;
	if (myBoxCollider->isCursorOver())
	{
		move = true;
	}
}

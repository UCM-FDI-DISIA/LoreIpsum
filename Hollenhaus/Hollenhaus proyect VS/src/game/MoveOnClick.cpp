#include "MoveOnClick.h"
#include "Entity.h"
#include "Manager.h"


MoveOnClick::MoveOnClick() : myBoxCollider()
{
}

MoveOnClick::~MoveOnClick()
{
}

void MoveOnClick::initComponent()
{
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	myBoxCollider = ent_->getComponent<BoxCollider>();
}

void MoveOnClick::update()
{
}

void MoveOnClick::OnLeftClickDown()
{
	Vector2D mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);

	if (myBoxCollider->isCursorOver())
	{
		std::cout << "\nAAAA\n";
	}
}

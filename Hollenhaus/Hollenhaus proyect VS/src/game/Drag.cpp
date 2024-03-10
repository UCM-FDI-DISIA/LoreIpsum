#include "pch.h"
#include "Drag.h"
#include "Manager.h"
#include "../sdlutils/InputHandler.h"

#include "BoxCollider.h"
#include "Transform.h"


Drag::Drag()
{


}

Drag::~Drag()
{
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
}

void Drag::initComponent()
{

	myTransform = mngr_->getComponent<Transform>(ent_);
	myBoxCollider = mngr_->getComponent<BoxCollider>(ent_);
	
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });


}

void Drag::update()
{
	if (isDraged) {

		Vector2D mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);

		Vector2D posAct = mousePos - initialMousePos + initialTransformPos;
		

		myTransform->getGlobalPos().set(posAct);
	}
}

void Drag::OnLeftClickDown()
{
	Vector2D mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);

	if (myBoxCollider->isCursorOver() && conditionsValid()) {
		isDraged = true;
		initialMousePos = mousePos;
		initialTransformPos = myTransform->getGlobalPos();

	}
}

void Drag::OnLeftClickUp()
{
	if (isDraged) {
		isDraged = false;


		SDL_Rect windowRect = build_sdlrect(0, 0, sdlutils().width(), sdlutils().height());
		if (!SDL_HasIntersection(myBoxCollider->getRect(),&windowRect )) {
			myTransform->getGlobalPos().set(initialTransformPos);//quitar? poner en otro component?

		}
	}

}

bool Drag::conditionsValid()
{
	if (conditions.size() == 0) return true;
	

	auto it = conditions.begin();

	while (it != conditions.end() && (*it)()) ++it;

	return it == conditions.end();
}

void Drag::addCondition(std::function<bool(void)> condition)
{
	conditions.push_back(condition);
}

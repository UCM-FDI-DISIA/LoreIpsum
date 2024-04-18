#include "pch.h"
#include "Button.h"

// ---- PRIVATES:
// Llama a todos los Callbacks
void Button::useCallback() const
{
	for (auto e : callbacks)
	{
		e();
	}
}

// ---- PUBLICS:
Button::Button()
{
	myBoxCollider = nullptr;
	currentState = MOUSE_OUT;

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
}

Button::~Button()
{
	ih().clearFunction(InputHandler::MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().clearFunction(InputHandler::MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
}

void Button::update()
{
	// Si el cursor esta sobre el boton pasan cosas
	if (myBoxCollider->isCursorOver())
	{
		currentState = MOUSE_OVER;
	}
	else
	{
		currentState == MOUSE_OUT;
	}
}

void Button::initComponent()
{
	myBoxCollider = mngr_->getComponent<BoxCollider>(ent_);
}

// Aniade callbacks a la lista
void Button::connectToButton(SDLEventCallback _callback)
{
	callbacks.push_back(_callback);
}

void Button::OnLeftClickDown()
{
	if (myBoxCollider->isCursorOver() && currentState == MOUSE_OVER)
	{
		currentState = MOUSE_CLICK;
		useCallback();
	}
}

void Button::OnLeftClickUp()
{
	currentState = MOUSE_OUT;
}

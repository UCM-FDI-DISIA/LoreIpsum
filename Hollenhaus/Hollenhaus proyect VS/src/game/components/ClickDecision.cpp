#include "pch.h"
#include "ClickDecision.h"

ClickDecision::ClickDecision(int decision)
{
	decision_ = decision;
	click_ = false;

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
}

void ClickDecision::initComponent()
{
}

void ClickDecision::update()
{
}

void ClickDecision::OnLeftClickDown()
{
	if (mouseRaycast() == ent_)
	{
		click_ = true;
		TakeDecision();
	}
}

void ClickDecision::OnLeftClickUp()
{
	click_ = false;
}

void ClickDecision::TakeDecision()
{
	switch (decision_) 
	{
	case 0:
		TuVieja("SI");
		break;

	case 1:
		TuVieja("BYEBYE");
		break;

	default:
		TuVieja("Esta decision no existe. Añadir en ClickDecision.cpp");
		break;
	}
}



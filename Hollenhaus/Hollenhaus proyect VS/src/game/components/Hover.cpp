#include "../pchs/pch.h"
#include "Hover.h"

void Hover::initComponent()
{
	tr = getEntity()->getComponent<Transform>();
	spr = getEntity()->getComponent<SpriteRenderer>();
	bc = getEntity()->getComponent<BoxCollider>();

	assert(tr != nullptr);
	assert(spr != nullptr);
	assert(bc != nullptr);

	iniScale = tr->getGlobalScale();
	iniPos = tr->getGlobalPos();
	iniLayer = getEntity()->getLayer();

	resetTweensForward();
}

void Hover::update()
{
	if (!isOnHand) return;

	const auto currTime = sdlutils().virtualTimer().currTime();
	//if (bc->isCursorOver() && !intoHover)
	if (mouseRaycast() == ent_)
	{
		if (!intoHover)
		{
			if (hoverTimer + hoverActivationSpeed <= currTime)
			{
				TuVieja(">>>>>>>>>>>>>>ENTRA HOVER *aplausos*");
				onHoverEnter();
			}
		}
	}
	else
	{
		hoverTimer = currTime; // se resetea el contador
		if (intoHover)
		{
			TuVieja(">>>>>>>>>>>>>>SALE HOVER *tristezas*");
			onHoverExit();
		}
	}

	//spr->setOffset(
	//	hoverTweenX.peek(),
	//	hoverTweenY.peek()
	//);
}

void Hover::onHoverEnter()
{
	intoHover = true;
	outoHover = false;
	/// ...
}

void Hover::onHoverExit()
{
	intoHover = false;
	outoHover = true;
	/// ...
}


void Hover::resetTweensForward()
{
	hoverTweenX =
		tweeny::from(iniPos.getX())
		.to(iniPos.getX() + hoverOffset.getX())
		.during(hoverSpeed)
		.via(tweeny::easing::sinusoidalInOut);

	hoverTweenY =
		tweeny::from(iniPos.getY())
		.to(iniPos.getY() + hoverOffset.getY())
		.during(hoverSpeed)
		.via(tweeny::easing::sinusoidalInOut);
}

void Hover::resetTweensBackward() /// *********
{
	// de vuelta de la posicion que sea a la inical
	hoverTweenX =
		tweeny::from(hoverTweenX.peek())
		.to(iniPos.getX())
		.during(hoverSpeed)
		.via(tweeny::easing::sinusoidalInOut);

	hoverTweenY =
		tweeny::from(hoverTweenY.peek())
		.to(iniPos.getY())
		.during(hoverSpeed)
		.via(tweeny::easing::sinusoidalInOut);
}

#include "../pchs/pch.h"
#include "Hover.h"

#include "basics/TextComponent.h"

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
				onHoverEnter();
			}
		}
	}
	else
	{
		hoverTimer = currTime; // se resetea el contador
		if (intoHover)
		{
			onHoverExit();
		}
	}

	hoverTweenX.step(1);
	hoverTweenY.step(1);

	updateEveryComponent();
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

void Hover::updateEveryComponent()
{
	//std::cout << hoverTweenX.peek() << std::endl;
	//std::cout << hoverTweenY.peek() << std::endl;

	//spr->setOffset(
	//	hoverTweenX.peek(),
	//	hoverTweenY.peek()
	//);

	//getEntity()->getComponent<Transform>()->setGlobalScale(hoverScale, hoverScale);
	//getEntity()->setEveryLayer(2);
	// ajusta tambien los textos
	//for (auto child : getEntity()->getComponent<Transform>()->getChildren())
	//{
	//	auto texto = child->getEntity()->getComponent<TextComponent>();
	//	if (texto != nullptr)
	//	{
	//		child->getRelativePos().set(
	//			child->getRelativePos().getX(),
	//			child->getRelativePos().getY() - child->getRelativePos().getY() / 6.25
	//		);
	//	}
	//}
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

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
	if (ih().keyDownEvent()) return;

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
			resetEveryComponent();
		}
	}

	hoverTweenX.step(1);
	hoverTweenY.step(1);

	if (intoHover)
	{
		updateEveryComponent();
	}
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
	// fondo de la carta
	spr->setOffset(
		hoverTweenX.peek(),
		hoverTweenY.peek()
	);

	//escala
	//getEntity()->getComponent<Transform>()->setGlobalScale(hoverScale, hoverScale);

	//layer creo que no hace falta
	//getEntity()->setEveryLayer(2);

	// textos
	for (const auto child : getEntity()->getComponent<Transform>()->getChildren())
	{
		// si es texto
		const auto texto = child->getEntity()->getComponent<TextComponent>();
		if (texto != nullptr)
		{
			texto->setOffset(
				hoverTweenX.peek(),
				hoverTweenY.peek()
			);
		}

		// si es imagen, puede tener texto
		const auto imagen = child->getEntity()->getComponent<SpriteRenderer>();
		if (imagen != nullptr)
		{
			imagen->setOffset(
				hoverTweenX.peek(),
				hoverTweenY.peek()
			);

			// los efectos tienen un texto adherido
			for (const auto nieto : child->getChildren())
			{
				// si es texto
				const auto texto = child->getEntity()->getComponent<TextComponent>();
				if (texto != nullptr)
				{
					texto->setOffset(
						hoverTweenX.peek(),
						hoverTweenY.peek()
					);
				}
			}
		}
	}
}

void Hover::resetEveryComponent()
{
	// fondo de la carta
	spr->setOffset(
		0,
		0
	);

	// textos
	for (const auto child : getEntity()->getComponent<Transform>()->getChildren())
	{
		// si es texto
		const auto texto = child->getEntity()->getComponent<TextComponent>();
		if (texto != nullptr)
		{
			texto->setOffset(
				0, 0
			);
		}

		// si es imagen, puede tener texto
		const auto imagen = child->getEntity()->getComponent<SpriteRenderer>();
		if (imagen != nullptr)
		{
			imagen->setOffset(0, 0);

			// los efectos tienen un texto adherido
			for (const auto nieto : child->getChildren())
			{
				// si es texto
				const auto texto = child->getEntity()->getComponent<TextComponent>();
				if (texto != nullptr)
					texto->setOffset(0, 0);
			}
		}
	}
}


void Hover::resetTweensForward()
{
	hoverTweenX =
		tweeny::from(0.f)
		.to(hoverOffset.getX())
		.during(hoverSpeed)
		.via(tweeny::easing::sinusoidalInOut);

	hoverTweenY =
		tweeny::from(0.f)
		.to(hoverOffset.getY())
		.during(hoverSpeed)
		.via(tweeny::easing::sinusoidalInOut);
}

void Hover::resetTweensBackward() /// *********
{
	// de vuelta de la posicion que sea a la inical
	hoverTweenX =
		tweeny::from(hoverTweenX.peek())
		.to(0.f)
		.during(hoverSpeed)
		.via(tweeny::easing::sinusoidalInOut);

	hoverTweenY =
		tweeny::from(hoverTweenY.peek())
		.to(0.f)
		.during(hoverSpeed)
		.via(tweeny::easing::sinusoidalInOut);
}

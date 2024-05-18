#include "..\pchs\pch.h"
#include "FadeComponent.h"

FadeComponent::FadeComponent()
{
}

FadeComponent::~FadeComponent()
{
}

void FadeComponent::initComponent()
{
	f = ent_->getComponent<SpriteRenderer>();

	//Creamos el tween
	// FADE TWEEN
	fadetween =
		tweeny::from(0)
		.to(255)
		.during(30)
		.via(tweeny::easing::linear);
}

void FadeComponent::update()
{
	//Poner bool para que solo se haga al principio?
	if (fadeIn) {
		fadetween.step(1); // avanza
		f->setOpacity(fadetween.peek());
	}
	else {
		fadetween.forward();
	}
	
}

void FadeComponent::FadeIn()
{
	fadeIn = false;
}



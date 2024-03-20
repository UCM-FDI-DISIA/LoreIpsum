#include "CardOnHover.h"

#include "SpriteRenderer.h"
#include "Manager.h"
#include "BoxCollider.h"
#include "Transform.h"

CardOnHover::CardOnHover()
{
}

CardOnHover::~CardOnHover()
{
}

void CardOnHover::initComponent()
{
	mySpriteRenderer = ent_->getComponent<SpriteRenderer>();
	myBoxCollider = ent_->getComponent<BoxCollider>();

	myTransform = ent_->getComponent<Transform>();

	previousScale = Vector2D(0.55f, 0.55f);

	scaleOnHover = previousScale * scaleMultiplier;
}

void CardOnHover::update()
{
	if (myBoxCollider->isCursorOver()) {

		myTransform->getGlobalScale().set(scaleOnHover);
	}
	else {
		myTransform->getGlobalScale().set(previousScale);
	}
}

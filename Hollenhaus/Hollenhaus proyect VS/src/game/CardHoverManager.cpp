#include "CardHoverManager.h"

#include "Manager.h"

#include "Transform.h"
#include "CardStateManager.h"


CardHoverManager::CardHoverManager()
{
}

CardHoverManager::~CardHoverManager()
{
}

void CardHoverManager::initComponent()
{
}

void CardHoverManager::update()
{
	ecs::entity_t card = mouseRaycast(ecs::grp::CARDS);

	if (card != nullptr) {

		auto cardStateM = card->getComponent<CardStateManager>();

		if (cardStateM->getState() == CardStateManager::ON_HAND) {
			hoverTransform = card->getComponent<Transform>();
		}
	}
	else {

	}

	if (hoverTransform != nullptr) {
		hoverTransform->getGlobalScale().set(2, 2);
	}
	
}

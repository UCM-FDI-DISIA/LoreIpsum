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

	//si detecto una carta y no tenia carta antes
	if (card != nullptr && hoverTransform == nullptr) {

		auto cardStateM = card->getComponent<CardStateManager>();

		//si la carta esta en mano
		if (cardStateM->getState() == CardStateManager::ON_HAND) {
			//guardar sus datos
			hoverTransform = card->getComponent<Transform>();
			previousLayer = card->getLayer();
	
			previousScale = hoverTransform->getRelativeScale();

			//seteo sus nuevos datos
			card->setLayer(layerOnHover);
			hoverTransform->getRelativeScale().set(previousScale * scaleMultiplier);
		}
	}
	else if(card != nullptr && hoverTransform != card->getComponent<Transform>()) {//si detecto una carta distinta



		auto cardStateM = card->getComponent<CardStateManager>();

		//si la carta esta en mano
		if (cardStateM->getState() == CardStateManager::ON_HAND) {

			//quitar la actual
			card->setLayer(previousLayer);
			hoverTransform->getRelativeScale().set(previousScale);

			//guardar sus datos
			hoverTransform = card->getComponent<Transform>();
			previousLayer = card->getLayer();

			previousScale = hoverTransform->getRelativeScale();

			//seteo sus nuevos datos
			card->setLayer(layerOnHover);
			hoverTransform->getRelativeScale().set(previousScale * scaleMultiplier);
		}
	}
	else if (card == nullptr && hoverTransform != nullptr) {//si no detecto una carta y ya tenia una antes
		hoverTransform->getEntity()->setLayer(previousLayer);
		hoverTransform->getRelativeScale().set(previousScale );
		hoverTransform = nullptr;
	}


	
	
}

#include "PlayerCardsManager.h"
#include "Manager.h"
#include "Entity.h"
#include "../sdlutils/InputHandler.h"

#include "CardFactory_v0.h"

void PlayerCardsManager::initComponent() {

	click = false;
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { drawCard(); });
}

void PlayerCardsManager::drawCard() {

	if (!click && ent_->getComponent<BoxCollider>()->isCursorOver() && deck_->deckSize()>0)
	{
		hand_->addCard(deck_->drawCard()->getEntity());
		TuVieja("AAAAAAAAAAAA");
	}

}
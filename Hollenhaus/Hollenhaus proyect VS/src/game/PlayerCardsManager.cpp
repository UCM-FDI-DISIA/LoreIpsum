#include "PlayerCardsManager.h"
#include "Manager.h"
#include "Entity.h"
#include "MatchManager.h"
#include "../sdlutils/InputHandler.h"

#include "CardFactory_v0.h"

void PlayerCardsManager::initComponent() {

	//click = false;
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { drawCard(); });
}

void PlayerCardsManager::drawCard() {
	//deck_->shuffle();

	if (deck_->deckSize() > 0 && 
		ent_->getComponent<BoxCollider>()->isCursorOver() && 
		hand_->handSize()< MAX_IN_HAND &&
		mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>()->getActualActionPoints() >= deck_->getDrawCardCost())
	{
		hand_->addCard(deck_->drawCard()->getEntity());
		TuVieja("AAAAAAAAAAAA");
	}

}
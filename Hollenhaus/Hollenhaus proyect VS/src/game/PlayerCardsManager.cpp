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
	const auto matchManager = mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>();
	const Players::Owner turnOwner = matchManager->getActualState() == MatchManager::TurnJ1
		? Players::PLAYER1 : Players::PLAYER2;

	if (deck_->deckSize() > 0 && 
		ent_->getComponent<BoxCollider>()->isCursorOver() && 
		hand_->handSize()< MAX_IN_HAND &&
		matchManager->getActualActionPoints() >= deck_->getDrawCardCost()
		&& deck_->getOwner() == turnOwner
		)
	{
		hand_->addCard(deck_->drawCard()->getEntity());
		//TuVieja("AAAAAAAAAAAA");
	}
}
#include "pch.h"
#include "PlayerCardsManager.h"
#include "Manager.h"
#include "Entity.h"
#include "MatchManager.h"
#include "../sdlutils/InputHandler.h"

#include "CardFactory_v0.h"

#include "../Cell.h"

void PlayerCardsManager::initComponent()
{
	//click = false;
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { drawCard(); });
}

PlayerCardsManager::~PlayerCardsManager()
{
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { drawCard(); });
}

void PlayerCardsManager::drawCard()
{
	//deck_->shuffle();
	// esto es porque me da un error rarísimo en el matchover
	if (mngr_ != nullptr && mngr_->getHandler(ecs::hdlr::MATCH_MANAGER) != nullptr)
	{
		const auto matchManager = mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>();
		const Players::Owner turnOwner = matchManager->getActualState() == MatchManager::TurnJ1
			                                 ? Players::PLAYER1
			                                 : Players::PLAYER2;

		if (deck_->deckSize() > 0 &&
			ent_->getComponent<BoxCollider>()->isCursorOver() &&
			hand_->handSize() < MAX_IN_HAND &&
			matchManager->getActivePlayerActualActionPoints() >= deck_->getDrawCardCost()
			&& deck_->getOwner() == turnOwner
		)
		{
			hand_->addCard(deck_->drawCard()->getEntity());
			//TuVieja("AAAAAAAAAAAA");
		}
	}
}

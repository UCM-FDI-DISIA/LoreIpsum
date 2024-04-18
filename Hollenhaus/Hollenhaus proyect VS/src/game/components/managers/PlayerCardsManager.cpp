#include "pch.h"
#include "PlayerCardsManager.h"
#include "Manager.h"
#include "../../Entity.h"
#include "MatchManager.h"
#include "../../../sdlutils/InputHandler.h"
#include "../../components/Cell.h"

class BoxCollider;

void PlayerCardsManager::initComponent()
{
	//click = false;
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { drawCard(); });
}

HandComponent* PlayerCardsManager::getHand()
{
	return hand_;
}

PlayerCardsManager::~PlayerCardsManager()
{
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { drawCard(); });
}

void PlayerCardsManager::drawCard()
{
	//deck_->shuffle();
	// esto es porque me da un error rarísimo en el matchover
	// LUIS: Creo que lo que está pasando es que al salir de MatchState, la función drawCard se queda en la lista de callbacks
	// asi que cuando el inputHandler recorre la lista de callbacks (el error salta al hacer click derecho) se encuentra con una
	// función drawCard que ya ha perdido su contexto. 
	// Supongo que hay que eliminar todas las funciones de la lista de callbacks siempre que salgamos de su contexto.
	if (mngr_ != nullptr && mngr_->getHandler(ecs::hdlr::MATCH_MANAGER) != nullptr)
	{
		const auto matchManager = mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>();

		const Players::Owner turnOwner =
			matchManager->getActualState() == Turns::J1
				? Players::PLAYER1
				: matchManager->getActualState() == Turns::J2
				? Players::PLAYER2
				: Players::NONE;

		if (deck_->deckSize() > 0 &&
			ent_->getComponent<BoxCollider>()->isCursorOver() &&
			hand_->handSize() < MAX_IN_HAND &&
			matchManager->getActualPlayerActualActionPoints() >= deck_->getDrawCardCost()
			&& deck_->getOwner() == turnOwner
		)
		{
			hand_->addCard(deck_->drawCard()->getEntity());
			//TuVieja("AAAAAAAAAAAA");
		}
	}
}

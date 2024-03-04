#include "PlayerCardsManager.h"
#include "Manager.h"
#include "Entity.h"
#include "../sdlutils/InputHandler.h"

#include "CardFactory_v0.h"

void PlayerCardsManager::initComponent() {

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { drawCard(); });
}

void PlayerCardsManager::drawCard() {
	hand_->addCard(deck_->drawCard()->getEntity());

}
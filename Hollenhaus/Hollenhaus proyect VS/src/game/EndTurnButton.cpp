#include "EndTurnButton.h"
#include "Manager.h"
#include "../sdlutils/InputHandler.h"ç
#include "MatchManager.h"

EndTurnButton::EndTurnButton(MatchManager::TurnState buttonPropietary) :
	buttonPropietary_(buttonPropietary)
{
}

EndTurnButton::~EndTurnButton()
{
}

void EndTurnButton::initComponent()
{
	tr_ = mngr_->getComponent<Transform>(ent_);
	bc_ = mngr_->getComponent<BoxCollider>(ent_);
	matchManager_ = mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>();

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { ClickButton(); });
}

void EndTurnButton::update()
{
}

void EndTurnButton::ClickButton()
{
	if (bc_->isCursorOver() && matchManager_->GetActualState() == buttonPropietary_) {
		// Se pasa el turno al otro jugador
		matchManager_->SetActualState(buttonPropietary_ == MatchManager::TurnState::TurnJ1 ? MatchManager::TurnState::TurnJ2 : MatchManager::TurnState::TurnJ1);
	}
}

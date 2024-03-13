#include "pch.h"
#include "EndTurnButton.h"
#include "managers/Manager.h"
#include "../../sdlutils/InputHandler.h"

#include "basics/BoxCollider.h"
#include "basics/Transform.h"

EndTurnButton::EndTurnButton(MatchManager::TurnState buttonPropietary) :
	buttonPropietary_(buttonPropietary)
{
}

EndTurnButton::~EndTurnButton()
{
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { ClickButton(); });
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
	// version con propietario:
	//if (bc_->isCursorOver() && matchManager_->setActualState() == buttonPropietary_) {
	//	// Se pasa el turno al otro jugador
	//	matchManager_->setActualState(buttonPropietary_ == MatchManager::TurnState::TurnJ1 ? MatchManager::TurnState::TurnJ2 : MatchManager::TurnState::TurnJ1);
	//}

	// version toggle
	if (bc_->isCursorOver()) {
		// Se pasa el turno al otro jugador
		matchManager_->setActualState(matchManager_->getActualState() == MatchManager::TurnState::TurnJ1 ? MatchManager::TurnState::TurnJ2 : MatchManager::TurnState::TurnJ1);
	}
}

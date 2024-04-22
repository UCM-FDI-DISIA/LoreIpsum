#include "pch.h"
#include "EndTurnButton.h"
#include "managers/Manager.h"
#include "../../sdlutils/InputHandler.h"

#include "basics/BoxCollider.h"
#include "basics/Transform.h"
#include "../TutorialManager.h"

EndTurnButton::EndTurnButton(Turns::State buttonPropietary) :
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

void EndTurnButton::setIA(bool b)
{
	activeIA = true;
}

void EndTurnButton::ClickButton()
{
	// version con propietario:
	//if (bc_->isCursorOver() && matchManager_->setActualState() == buttonPropietary_) {
	//	// Se pasa el turno al otro jugador
	//	matchManager_->setActualState(buttonPropietary_ == MatchManager::TurnState::TurnJ1 ? MatchManager::TurnState::TurnJ2 : MatchManager::TurnState::TurnJ1);
	//}

	// version toggle
	//if (bc_->isCursorOver()) {
	//	// Se pasa el turno al otro jugador
	//	matchManager_->setActualState(matchManager_->getActualState() == Turns::J1 ? Turns::J2 : Turns::J1);
	//}

	//version con IA
	if (activeIA) {

		if (bc_->isCursorOver() && matchManager_->getActualState() == Turns::J1) {
			// Se pasa el turno al otro jugador
			matchManager_->setActualState(Turns::IA);

			// TUTORIAL COSAS
			ecs::entity_t ent = GameStateMachine::instance()->getMngr()->getHandler(ecs::hdlr::TUTORIAL_MANAGER);
			if (ent->hasComponent<TutorialManager>()) {
				ent->getComponent<TutorialManager>()->tutorialActionEnded(Tutorials::Tutorials::BOARD, Tutorials::Board::PRESS_NEXT_TURN);
				ent->getComponent<TutorialManager>()->tutorialActionEnded(Tutorials::Tutorials::BOARD, Tutorials::Board::NEXT_CARD_1);

			}
		}
	}
}

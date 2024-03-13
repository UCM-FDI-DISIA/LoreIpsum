#include "pch.h"
#include "DragManager.h"
#include "../../../sdlutils/InputHandler.h"
#include "../basics/Transform.h"
#include "Manager.h"
#include "../../GameStateMachine.h"
#include "../basics/BoxCollider.h"
#include "../DropDetector.h"
#include "CardStateManager.h"

#include "../Cell.h"
#include "../Card.h"
#include "BoardManager.h"
#include "../HandComponent.h"
#include "MatchManager.h"

DragManager::DragManager()
{
}

DragManager::~DragManager()
{
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
}

void DragManager::initComponent()
{
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });

	dragTransform = nullptr;
}

void DragManager::update()
{
	//si tenemos carta drageada...

	if (dragTransform != nullptr) {
		//actualizamos su posicion teniendo en cuenta la posicion del raton

		Vector2D mousePos (ih().getMousePos().first, ih().getMousePos().second);
		Vector2D posAct = (mousePos - initialMousePos) + initialTransformPos;

		dragTransform->setGlobalPos(posAct);
	}

}

void DragManager::OnLeftClickDown()
{
	//buscar una colision con una entidad del grupo carta

	auto card = mouseRaycast(ecs::grp::CARDS);

	if (card != nullptr && CardOnHand(card) && CardIsOfCurrentPlayer(card)) 
	{
		//se guarda la posicion/ transform de como estaba la carta
		dragTransform = card->getComponent<Transform>();

		initialTransformPos.set(dragTransform->getGlobalPos());
		initialMousePos.set(Vector2D(ih().getMousePos().first, ih().getMousePos().second));

	}

}

void DragManager::OnLeftClickUp()
{
	//si no tenemos carta drageada, no hacemos nada

	//si, si la tenemos, verificamos colisiones con el grupo DropDetector
	if (dragTransform != nullptr) {

		auto drop = mouseRaycast(ecs::grp::DROPS);

		auto dropDetector = drop != nullptr ? drop->getComponent<DropDetector>() : nullptr;

		//si tenemos una colision con el drop detector, cambiamos la posicion de la carta por la que guarde el drop
		//también confirmamos que tenemos suficientes puntos de acción para lanzar la carta
		if (drop != nullptr && 
			!dropDetector->isOcuped() && enoughPoints(dragTransform->getEntity()))
		{
			//colocar la carta en su sitio(posicion en la pantalla)
			dragTransform->setGlobalPos(dropDetector->getCardPos());
			
			//coloca la carta en la celda y la quita de la manos
			dragTransform->getEntity()->getComponent<CardStateManager>()->putOnBoard();

			//la celda esta ocupada
			dropDetector->setOcuped(true);

			//mandar la info al tablero
			putCardOnBoard(dragTransform->getEntity(), dropDetector);
		}
		else {//sino, devolvemos la carta a su posicion inicial
			dragTransform->setGlobalPos(initialTransformPos);
		}

		//en cualquier caso, ya no tenemos carta drageada
		dragTransform = nullptr;
	}

}

bool DragManager::CardOnHand(ecs::entity_t card)
{
	return card->getComponent<CardStateManager>()->getState() == CardStateManager::ON_HAND;
}


//returns true if card is belongs to the player who have the turn
bool DragManager::CardIsOfCurrentPlayer(ecs::entity_t card)
{
	const auto matchManager = mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>();

	const Players::Owner turnOwner = matchManager->getActualState() == MatchManager::TurnJ1
		? Players::PLAYER1 : Players::PLAYER2;

	Players::Owner cardOwner = Players::NULO;

	//setear la carta en funcion de donde hemos clickado
	if (card != nullptr
		&& card->getComponent<Transform>() != nullptr
		&& card->getComponent<Transform>()->getParent() != nullptr) {

		cardOwner = card->getComponent<Transform>()->getParent()->getEntity()->getComponent<HandComponent>()->getOwner();
	}

	return cardOwner == turnOwner;
}

//card must hava a Card component
bool DragManager::enoughPoints(ecs::entity_t card)
{
	return card->getComponent<Card>()->getCost() <= mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>()->getActualPlayerActualActionPoints();
}

void DragManager::putCardOnBoard(ecs::entity_t card, DropDetector* cell)
{

	//x,y dependen del dropDectector(Cell)
			//card viene del dragTransform
			//owner depende del match manager,

	int x = cell->getBoardPos().getX();
	int y = cell->getBoardPos().getY();
	Card* cardComp = card->getComponent<Card>();

	Players::Owner playerTurn = mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>()->getPlayerTurn();

	boardManager->setCard(x, y, cardComp, playerTurn);
}


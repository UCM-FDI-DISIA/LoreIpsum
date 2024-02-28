#include "DragManager.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"
#include "Manager.h"
#include "GameStateMachine.h"
#include "BoxCollider.h"
#include "DropDetector.h"
#include "CardStateManager.h"

#include "../Cell.h"
#include "Card.h"
#include "BoardManager.h"

DragManager::DragManager()
{
}

DragManager::~DragManager()
{
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

	if (card != nullptr && //si hay carta y esta en la mano
		card->getComponent<CardStateManager>()->getState() == CardStateManager::ON_HAND) {

		//se guarda la posicion/ transform de como estaba la carta
		dragTransform = card->getComponent<Transform>();

		initialTransformPos.set(dragTransform->getGlobalPos());
		initialMousePos.set(Vector2D(ih().getMousePos().first, ih().getMousePos().second));

		//dragTransform->getGlobalPos().set(ih().getMousePos().first, ih().getMousePos().second);
	}


}

void DragManager::OnLeftClickUp()
{
	//si no tenemos carta drageada, no hacemos nada

	//si, s� la tenemos, verifcamos colisiones con el grupo DropDetector
	if (dragTransform != nullptr) {

		auto drop = mouseRaycast(ecs::grp::DROPS);

		//si tenemos una colision con el drop detector, cambiamos la posicion de la carta por la que guarde el drop
		if (drop != nullptr) {
			dragTransform->setGlobalPos(mngr().getComponent<DropDetector>(drop)->getCardPos());
			
			dragTransform->getEntity()->getComponent<CardStateManager>()->setState(CardStateManager::ON_CELL);

			//x,y dependen del dropDectector(Cell)
			//card viene del dragTransform
			//owner depende del match manager,
			
			int x = drop->getComponent<DropDetector>()->getBoardPos().getX();
			int y = drop->getComponent<DropDetector>()->getBoardPos().getY();
			Card* card = dragTransform->getEntity()->getComponent<Card>();
			
			boardManager->setCard(x, y, card, CellData::PLAYER1);
			//boardManager->setCard()
		}
		else {//sino, devolvemos la carta a su posicion inicial
			dragTransform->setGlobalPos(initialTransformPos);
		}

		//en cualquier caso, ya no tenemos carta drageada

		dragTransform = nullptr;
	}


}

#include "DragManager.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"
#include "Manager.h"
#include "GameStateMachine.h"
#include "BoxCollider.h"
#include "DropDetector.h"
#include "CardStateManager.h"



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

		Vector2D mousePos = Vector2D(ih().getMousePos().first, ih().getMousePos().second);
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

		dragTransform->getGlobalPos().set(ih().getMousePos().first, ih().getMousePos().second);
	}

	
}

void DragManager::OnLeftClickUp()
{
	//si no tenemos carta drageada, no hacemos nada

	//si, sí la tenemos, verifcamos colisiones con el grupo DropDetector
	if (dragTransform != nullptr) {

		auto drag = mouseRaycast(ecs::grp::DROPS);

		//si tenemos una colision con el drop detector, cambiamos la posicion de la carta por la que guarde el drop
		if (drag != nullptr) {
			dragTransform->getGlobalPos().set(mngr().getComponent<DropDetector>(drag)->getCardPos());
			
			dragTransform->getEntity()->getComponent<CardStateManager>()->setState(CardStateManager::ON_CELL);
		}
		else {//sino, devolvemos la carta a su posicion inicial
			dragTransform->getGlobalPos().set(initialTransformPos);
		}

		//en cualquier caso, ya no tenemos carta drageada
			
		dragTransform = nullptr;
	}


}

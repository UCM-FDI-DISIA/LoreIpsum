#include <../pchs/pch.h>

#include "SolDragComponent.h"
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"
#include "basics/Transform.h"
#include "../../game/components/managers/Manager.h"
#include "../GameStateMachine.h"
#include "../../game/components/basics/BoxCollider.h"
#include "DropDetector.h"

#include "SolCardComponent.h"

SolDragComponent::SolDragComponent()
{
}

SolDragComponent::~SolDragComponent()
{
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
}

void SolDragComponent::initComponent()
{
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });

	dragTransform = nullptr;
}

void SolDragComponent::update()
{
	//si tenemos carta drageada...

	if (dragTransform != nullptr) {
		//actualizamos su posicion teniendo en cuenta la posicion del raton

		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
		Vector2D posAct = (mousePos - initialMousePos) + initialTransformPosWithOffSet;

		dragTransform->setGlobalPos(posAct);

	}

}

void SolDragComponent::OnLeftClickDown()
{
	//buscar una colision con una entidad del grupo carta

	auto card = mouseRaycast(ecs::grp::SOLITAIRECARDS);

	if (card != nullptr && draggable)
	{
		//se guarda la posicion/ transform de como estaba la carta
		dragTransform = card->getComponent<Transform>();

		initialTransformPos.set(dragTransform->getGlobalPos());
		initialMousePos.set(Vector2D(ih().getMousePos().first, ih().getMousePos().second));

		initialTransformPosWithOffSet.set(initialMousePos - Vector2D(card->getComponent<BoxCollider>()->getRect()->w / 2, card->getComponent<BoxCollider>()->getRect()->h / 2));

	}
}

void SolDragComponent::OnLeftClickUp()
{
	//si no tenemos carta drageada, no hacemos nada

	//si, si la tenemos, verificamos colisiones con el grupo DropDetector
	if (dragTransform != nullptr) {

		auto drop = mouseRaycast(ecs::grp::DROPS);

		auto dropDetector = ((drop != nullptr) ? drop->getComponent<DropDetector>() : nullptr);

		//si tenemos una colision con el drop detector, cambiamos la posicion de la carta por la que guarde el drop
		if (drop != nullptr &&
			!dropDetector->isOcuped())
		{
			//coloca la carta en la celda y la quita del mazo
			//dragTransform->getEntity()->getComponent<CardStateManager>()->putOnBoard(); asi se hace en el otro 

			//la celda esta ocupada
			dropDetector->setOcuped(true);

			//mandar la info al tablero
			//putCardOnBoard(dragTransform->getEntity(), dropDetector); asi se hace en el otro


		}
		else 
		{
			//si no, devolvemos la carta a su posicion inicial
			dragTransform->setGlobalPos(initialTransformPos);
		}

		//en cualquier caso, ya no tenemos carta drageada
		dragTransform = nullptr;
	}

}

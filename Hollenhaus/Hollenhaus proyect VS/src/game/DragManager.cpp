#include "DragManager.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"
#include "Manager.h"
#include "GameStateMachine.h"
#include "BoxCollider.h"
#include "DropDetector.h"



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

		dragTransform->getGlobalPos().set(posAct);
	}
	
}

void DragManager::OnLeftClickDown()
{
	//buscar una colision con una entidad del grupo carta( FALTA :teniendo en cuenta el order in layer)

	auto cards = mngr().getEntities(ecs::grp::CARDS);

	auto it = cards.begin();

	while (it != cards.end() && !mngr().getComponent<BoxCollider>((*it))->isCursorOver()) ++it;

	//si encuentra una, esa entidad pasa a ser el transform draged
	if (it != cards.end()) {
		
		//se guarda la posicion/ transform de como estaba la carta
		dragTransform = mngr().getComponent<Transform>((*it));

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

		//verifcamos colisiones con el grupo DropDetector
		auto drops = mngr().getEntities(ecs::grp::DROPS);

		auto it = drops.begin();

		while (it != drops.end() && !mngr().getComponent<BoxCollider>((*it))->isCursorOver())++it;

		
		//si tenemos una colision con el drop detector, cambiamos la posicion de la carta por la que guarde el drop
		if (it != drops.end()) {
			dragTransform->getGlobalPos().set(mngr().getComponent<DropDetector>((*it))->getCardPos());
		}
		else {//sino, devolvemos la carta a su posicion inicial
			dragTransform->getGlobalPos().set(initialTransformPos);
		}

		//en cualquier caso, ya no tenemos carta drageada
			
		dragTransform = nullptr;
	}



	

}

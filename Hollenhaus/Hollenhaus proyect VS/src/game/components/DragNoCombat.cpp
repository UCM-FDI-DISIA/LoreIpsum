#include "pch.h"
#include "DragNoCombat.h"
#include "managers/Manager.h"
#include "../../sdlutils/InputHandler.h"
#include "basics/BoxCollider.h"
#include "basics/Transform.h"
#include "DropZone.h"

DragNoCombat::DragNoCombat() {}

DragNoCombat::~DragNoCombat()
{
	// se desuscribe de la funcion del input
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
}

void DragNoCombat::initComponent()
{
	// se suscribe a la funcion del input
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });

	dragTransform = nullptr;
}

void DragNoCombat::update()
{
	// si se esta agarrando la carta
	if (dragTransform != nullptr)
	{
		// guarda la posicion del raton en cada instante
		Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);

		// guarda la pos actual real para que la carta siga segun donde has pulsado para arrastrar
		Vector2D posAct = mousePos - initialMousePos + initialTransformPos;

		// establece la posicion actual  
		dragTransform->setGlobalPos(posAct);
		//std::cout << "PosAct: " << posAct << std::endl;
		//std::cout << "PosCarta: " << dragTransform->getGlobalPos() << std::endl;
	}
}

void DragNoCombat::OnLeftClickDown()
{
	// buscar una colision con una entidad del grupo carta
	auto card = mouseRaycast(ecs::grp::CARDS);

	// si se tiene carta
	if (card != nullptr)
	{
		// guardas el transform de la carta que agarres
		dragTransform = card->getComponent<Transform>();

		// se guarda la posicion original de la carta
		initialTransformPos.set(dragTransform->getGlobalPos());

		// guardas la posicion original del raton al momento de agarrar la carta
		initialMousePos.set(Vector2D(ih().getMousePos().first, ih().getMousePos().second));

		// estableces el initial transform real
		initialTransformPosWithOffSet.set(initialMousePos - Vector2D(card->getComponent<BoxCollider>()->getRect()->w / 2,
			card->getComponent<BoxCollider>()->getRect()->h / 2));
	}
}

void DragNoCombat::OnLeftClickUp()
{
	// si no tenemos carta draggeada, no hacemos nada
	// si la tenemos, verificamos colisiones con el grupo DROP_ZONE

	// si se suelta el cursor y se tenia carta
	if (dragTransform != nullptr)
	{
		ecs::entity_t ent = mouseRaycast(ecs::grp::DROPZONE);
		if (ent != nullptr) {
			DropZone* dp = ent->getComponent<DropZone>();
			if (dp != nullptr && dp->isOnDropZone(dragTransform))
			{
				if (ent->getComponent<PizarraManager>() != nullptr)
				{
					if (!ent->getComponent<PizarraManager>()->isPizarraLlena() || ent->getComponent<PizarraManager>()->isOnPizarra(dragTransform->getEntity()->getComponent<Card>()->getID()))
					{
						dp->useCallback(dragTransform->getEntity()->getComponent<Card>());
					}
				}
				else if ((ent->getComponent<DrawerManager>() != nullptr) &&
					!ent->getComponent<DrawerManager>()->isOnDrawer(dragTransform->getEntity()->getComponent<Card>()->getID()))
				{
					dp->useCallback(dragTransform->getEntity()->getComponent<Card>());
				}
				else {//sino, devolvemos la carta a su posicion inicial
					dragTransform->setGlobalPos(initialTransformPos);
				}
			}
			else {//sino, devolvemos la carta a su posicion inicial
				dragTransform->setGlobalPos(initialTransformPos);
			}
		}
		else {//sino, devolvemos la carta a su posicion inicial
			dragTransform->setGlobalPos(initialTransformPos);
		}

		//en cualquier caso, ya no tenemos carta drageada
		dragTransform = nullptr;
	}
}
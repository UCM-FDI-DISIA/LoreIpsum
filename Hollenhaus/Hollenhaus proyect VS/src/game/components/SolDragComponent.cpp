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

	// si hay carta y no esta bocabajo
	if (card != nullptr && !card->getComponent<SolCardComponent>()->getFaceDown())
	{

		//se guarda la posicion/ transform de como estaba la carta
		dragTransform = card->getComponent<Transform>();

		initialTransformPos.set(dragTransform->getGlobalPos());
		initialMousePos.set(Vector2D(ih().getMousePos().first, ih().getMousePos().second));

		initialTransformPosWithOffSet.set(initialMousePos - Vector2D(card->getComponent<BoxCollider>()->getRect()->w / 2, card->getComponent<BoxCollider>()->getRect()->h / 2));

		makeTopCardsChildren(dragTransform);
	}
}

void SolDragComponent::OnLeftClickUp()
{
	//si no tenemos carta drageada, no hacemos nada

	//si si la tenemos, verificamos colisiones con el grupo DropDetector
	if (dragTransform != nullptr) {

		auto dragLayer = dragTransform->getEntity()->getLayer();

		dragTransform->getEntity()->setLayer(-1);

		auto carta = mouseRaycast(ecs::grp::SOLITAIRECARDS); //carta sobre la que se suelta
		auto casilla = mouseRaycast(ecs::grp::SOLITAIRERIGHTCELL); //casilla sobre la que se suelta

		dragTransform->getEntity()->setLayer(dragLayer);

		auto cartaAgarrada = dragTransform->getEntity()->getComponent<SolCardComponent>(); //carta que tengo en la mano
		SolCardComponent::tipo tCartaAgarrada = cartaAgarrada->getTipo();


		if (casilla != nullptr) {

			SolCardComponent::tipo tCasilla = casilla->getComponent<SolCardComponent>()->getTipo();

			if (carta != nullptr && carta->getComponent<Transform>() != dragTransform) //si hay casilla y carta
			{
				if (carta->getComponent<SolCardComponent>()->getStacked()) 
				{
					if ((carta->getComponent<SolCardComponent>()->getTipo() == cartaAgarrada->getTipo()) &&
						(carta->getComponent<SolCardComponent>()->getNumber() == cartaAgarrada->getNumber() - 1)) 
					{
						auto newPos = carta->getComponent<Transform>()->getGlobalPos();
						dragTransform->getEntity()->getComponent<Transform>()->setGlobalPos(newPos);
						dragTransform->getEntity()->getComponent<SolCardComponent>()->setLayer(carta->getLayer() + 2);
						cartaAgarrada->setStacked(true);
						resetParent(dragTransform);
						cartaAgarrada->setCardOnBottom(nullptr);
					}
					else
					{
						//si no, devolvemos la carta a su posicion inicial
						dragTransform->setGlobalPos(initialTransformPos);
					}
				}
			}
			else // casilla y no carta
			{
				if (tCasilla == cartaAgarrada->getTipo() && cartaAgarrada->getNumber() == 1)
				{
					auto newPos = casilla->getComponent<Transform>()->getGlobalPos();
					dragTransform->getEntity()->getComponent<Transform>()->setGlobalPos(newPos);
					dragTransform->getEntity()->getComponent<SolCardComponent>()->setLayer(carta->getLayer() + 1);
					cartaAgarrada->setStacked(true);
					resetParent(dragTransform);
					cartaAgarrada->setCardOnBottom(nullptr);
				}
				else
				{
					//si no, devolvemos la carta a su posicion inicial
					dragTransform->setGlobalPos(initialTransformPos);
				}
			}
		}
		else if (carta != nullptr) //solo carta
		{
			auto cartaEncima = carta->getComponent<SolCardComponent>()->getCardOnTop(); //carta encima de la carta sobre la que se suelta

			SolCardComponent::tipo tCartaMesa = carta->getComponent<SolCardComponent>()->getTipo();

			auto distintoColor =
				(((tCartaAgarrada == SolCardComponent::spades || tCartaAgarrada == SolCardComponent::clubs) &&
					(tCartaMesa == SolCardComponent::hearts || tCartaMesa == SolCardComponent::diamonds))
					||
					((tCartaAgarrada == SolCardComponent::hearts || tCartaAgarrada == SolCardComponent::diamonds) &&
						(tCartaMesa == SolCardComponent::spades || tCartaMesa == SolCardComponent::clubs)));

			//si puedo dejar la carta encima de otra carta
			if ((cartaEncima == nullptr && (carta->getComponent<SolCardComponent>()->getNumber() == cartaAgarrada->getNumber() + 1) && distintoColor && !carta->getComponent<SolCardComponent>()->getStacked()))
			{
				auto newPos = carta->getComponent<Transform>()->getGlobalPos() + cartaAgarrada->getOffset();
				dragTransform->getEntity()->getComponent<Transform>()->setGlobalPos(newPos);
				dragTransform->getEntity()->getComponent<SolCardComponent>()->setLayer(carta->getLayer() + 1);
				resetParent(dragTransform);
				carta->getComponent<SolCardComponent>()->setCardOnTop(cartaAgarrada);
				cartaAgarrada->setCardOnBottom(nullptr);
			}
			else
			{
				//si no, devolvemos la carta a su posicion inicial
				dragTransform->setGlobalPos(initialTransformPos);
			}
		}
		else 
		{
			//si no, devolvemos la carta a su posicion inicial
			dragTransform->setGlobalPos(initialTransformPos);
		}



	}

	//en cualquier caso, ya no tenemos carta drageada
	resetParent(dragTransform);
	dragTransform = nullptr;

}

void SolDragComponent::makeTopCardsChildren(Transform* parent)
{
	auto cardComp = parent->getEntity()->getComponent<SolCardComponent>();

	while (cardComp->getCardOnTop() != nullptr) 
	{
		cardComp->getCardOnTop()->getEntity()->getComponent<Transform>()->addParent(parent);
		cardComp->getCardOnTop()->getEntity()->getComponent<Transform>()->setGlobalScale(0.8,0.8);
		cardComp = cardComp->getCardOnTop();
	}

}

void SolDragComponent::resetParent(Transform* parent)
{
	auto cardComp = parent->getEntity()->getComponent<SolCardComponent>();

	while (cardComp->getCardOnTop() != nullptr)
	{
		cardComp->getCardOnTop()->getEntity()->getComponent<Transform>()->removeParent();
		cardComp->getCardOnTop()->getEntity()->getComponent<Transform>()->setGlobalScale(0.8, 0.8);
		cardComp = cardComp->getCardOnTop();
	}
}

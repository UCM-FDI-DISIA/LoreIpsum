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

		//guardamos la layer de la carta en mano, y la colocamos atras, para q no afecte al raycast
		auto dragLayer = dragTransform->getEntity()->getLayer();

		setLayerTopCards(dragTransform, -10);

		//raycast para ver si hemos tocado alguna carta/ casilla
		auto carta = mouseRaycast(ecs::grp::SOLITAIRECARDS); //carta sobre la que se suelta
		auto casilla = mouseRaycast(ecs::grp::SOLITAIRERIGHTCELL); //casilla sobre la que se suelta

		//resetear la layer
		resetLayerTopCards(dragTransform, dragLayer);

		auto cartaAgarrada = dragTransform->getEntity()->getComponent<SolCardComponent>(); //carta que tengo en la mano
		SolCardComponent::tipo tCartaAgarrada = cartaAgarrada->getTipo();


		if (casilla != nullptr) {

			SolCardComponent::tipo tCasilla = casilla->getComponent<SolCardComponent>()->getTipo();

			if (carta != nullptr && carta->getComponent<Transform>() != dragTransform) //si hay casilla y carta
			{
				if ((carta->getComponent<SolCardComponent>()->getTipo() == cartaAgarrada->getTipo()) &&
					(carta->getComponent<SolCardComponent>()->getNumber() == cartaAgarrada->getNumber() - 1)) //mismo tipo y la de la mano es justo la siguiente mayor
				{
					//colocar la carta
					auto newPos = carta->getComponent<Transform>()->getGlobalPos();
					dragTransform->setGlobalPos(newPos);

					//ajustar la layer para que este encima
					dragTransform->getEntity()->getComponent<SolCardComponent>()->setLayer(carta->getLayer() + 2);

					//la carta que antes tenia abajo deja de tener a esta encima
					if (cartaAgarrada->getCardOnBottom() != nullptr) {
						cartaAgarrada->getCardOnBottom()->setCardOnTop(nullptr);
					}

					//esta carta, tiene a la carta de la mesa abajo, a lo mejor hay q cambiar nullptr por carta
					cartaAgarrada->setCardOnBottom(nullptr);


					//resetear los  hijos
					resetParent(dragTransform);
				}
				else
				{
					//si no, devolvemos la carta a su posicion inicial
					dragTransform->setGlobalPos(initialTransformPos);
				}

			}
			else // casilla y no carta
			{
				if (tCasilla == cartaAgarrada->getTipo() && cartaAgarrada->getNumber() == 1)//si es un AS del tipo de la casilla
				{
					//colocar carta
					auto newPos = casilla->getComponent<Transform>()->getGlobalPos();
					dragTransform->setGlobalPos(newPos);

					//dragTransform->getEntity()->getComponent<SolCardComponent>()->setLayer(carta->getLayer() + 1);

					//la carta que antes tenia abajo deja de tener a esta encima
					if (cartaAgarrada->getCardOnBottom() != nullptr) {
						cartaAgarrada->getCardOnBottom()->setCardOnTop(nullptr);
					}

					//el as no tiene a nadie abajo
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

			SolCardComponent::tipo tCartaMesa = carta->getComponent<SolCardComponent>()->getTipo();

			auto distintoColor =
				(((tCartaAgarrada == SolCardComponent::spades || tCartaAgarrada == SolCardComponent::clubs) &&
					(tCartaMesa == SolCardComponent::hearts || tCartaMesa == SolCardComponent::diamonds))
					||
					((tCartaAgarrada == SolCardComponent::hearts || tCartaAgarrada == SolCardComponent::diamonds) &&
						(tCartaMesa == SolCardComponent::spades || tCartaMesa == SolCardComponent::clubs)));


			bool noCartaEncima = carta->getComponent<SolCardComponent>()->getCardOnTop() == nullptr; //carta encima de la carta sobre la que se suelta
			//si puedo dejar la carta encima de otra carta
			if ((noCartaEncima &&
				(carta->getComponent<SolCardComponent>()->getNumber() == cartaAgarrada->getNumber() + 1) &&
				distintoColor))
			{
				//colocar carta
				auto newPos = carta->getComponent<Transform>()->getGlobalPos() + cartaAgarrada->getOffset();
				dragTransform->getEntity()->getComponent<Transform>()->setGlobalPos(newPos);

				//colocar cartas hijas

				//actualizar la nueva posicion
				newPos = Vector2D(newPos.getX(), newPos.getY() + cartaAgarrada->getOffset().getY());

				auto cartaSig = cartaAgarrada->getCardOnTop();

				while (cartaSig != nullptr) {
					cartaSig->getEntity()->getComponent<Transform>()->setGlobalPos(newPos);

					cartaSig = cartaSig->getCardOnTop();
					newPos = Vector2D(newPos.getX(), newPos.getY() + cartaAgarrada->getOffset().getY());
				}

				//ajustar layer
				auto newLayer = carta->getLayer() + 2;

				dragTransform->getEntity()->getComponent<SolCardComponent>()->setLayer(newLayer);
				newLayer += 2;
				//ajustar layer hijas

				cartaSig = cartaAgarrada->getCardOnTop();

				while (cartaSig != nullptr) {
					cartaSig->setLayer(newLayer);

					cartaSig = cartaSig->getCardOnTop();
					newLayer += 2;
				}


				//la carta que antes tenia abajo deja de tener a esta encima
				if (cartaAgarrada->getCardOnBottom() != nullptr) {
					cartaAgarrada->getCardOnBottom()->setCardOnTop(nullptr);
				}

				//nueva carta abajo
				cartaAgarrada->setCardOnBottom(carta->getComponent<SolCardComponent>());

				//la carta de abajo tiene a esta encima
				carta->getComponent<SolCardComponent>()->setCardOnTop(cartaAgarrada);

				//para las cartas de encima
				resetParent(dragTransform);
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



		//en cualquier caso, ya no tenemos carta drageada
		resetParent(dragTransform);
		dragTransform = nullptr;
	}



}

void SolDragComponent::makeTopCardsChildren(Transform* parent)
{
	auto cardComp = parent->getEntity()->getComponent<SolCardComponent>();

	while (cardComp->getCardOnTop() != nullptr)
	{
		cardComp->getCardOnTop()->getEntity()->getComponent<Transform>()->addParent(parent);
		cardComp->getCardOnTop()->getEntity()->getComponent<Transform>()->setGlobalScale(0.8, 0.8);
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

void SolDragComponent::setLayerTopCards(Transform* parent, int layer)
{
	auto cardComp = parent->getEntity()->getComponent<SolCardComponent>();

	parent->getEntity()->getComponent<SolCardComponent>()->setLayer(layer);

	while (cardComp->getCardOnTop() != nullptr)
	{
		cardComp->getCardOnTop()->setLayer(layer);
		cardComp = cardComp->getCardOnTop();
	}
}

void SolDragComponent::resetLayerTopCards(Transform* parent, int layer)
{
	auto cardComp = parent->getEntity()->getComponent<SolCardComponent>();

	auto currLayer = layer;

	parent->getEntity()->getComponent<SolCardComponent>()->setLayer(layer);
	currLayer += 2;


	while (cardComp->getCardOnTop() != nullptr)
	{
		cardComp->getCardOnTop()->setLayer(currLayer);
		cardComp = cardComp->getCardOnTop();
		currLayer += 2;
	}
}

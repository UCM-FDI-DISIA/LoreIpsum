#include <../pchs/pch.h>

#include "DragManager.h"
#include "../../../sdlutils/SDLUtils.h"
#include "../../../sdlutils/InputHandler.h"
#include "../basics/Transform.h"
#include "Manager.h"
#include "../../GameStateMachine.h"
#include "../basics/BoxCollider.h"
#include "../DropDetector.h"
#include "CardStateManager.h"
#include "../../TutorialManager.h"

#include "../Cell.h"
#include "../Card.h"
#include "../ShineComponent.h"
#include "BoardManager.h"
#include "../HandComponent.h"
#include "MatchManager.h"

#include "../multiplayer/NetGame.h"

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
		Vector2D posAct = (mousePos - initialMousePos) + initialTransformPosWithOffSet;

		dragTransform->setGlobalPos(posAct);

		updateFeedback();

	}

}

void DragManager::updateFeedback()
{
	ecs:: entity_t drop = mouseRaycast(ecs::grp::DROPS);

	auto dropDetector = drop != nullptr ? drop->getComponent<DropDetector>() : nullptr;

	//Si una carta está pillada empieza el feedback
	if (drop != nullptr) {

		//Feedback que indica sobre qué casilla va a caer la carta
		colorEffects(drop);
		drop->getComponent<ShineComponent>()->setShine();

		//Si cambiamos la celda sobre la que está puesta la carta
		if (lastCell != nullptr && lastCell != drop) {

			//Quitamos los colores del drag anterior
			boardManager->returnColors();
			lastCell->getComponent<ShineComponent>()->outShine();
			lastCell = drop;
		}
		else {

			lastCell = drop;
			colorEffects(drop);
		}
		
	}
	else {
		boardManager->returnColors();
		if (lastCell != nullptr) lastCell->getComponent<ShineComponent>()->outShine();
		}
}
void DragManager::setNetGame(NetGame* _netGame)
{
	netGame = _netGame;
}

void DragManager::playCardMultiplayer(ecs::entity_t e ,Vector2D pos)
{
	if (netGame != nullptr) {
		TuVieja("Se envia el mesaje de jugar una carta");
		netGame->playCard(e, pos);
	}
}


void DragManager::OnLeftClickDown()
{
	//buscar una colision con una entidad del grupo carta

	auto card = mouseRaycast(ecs::grp::CARDS);

	if (card != nullptr && draggable && CardOnHand(card) && CardIsOfCurrentPlayer(card)) 
	{
		//se guarda la posicion/ transform de como estaba la carta
		dragTransform = card->getComponent<Transform>();

		initialTransformPos.set(dragTransform->getGlobalPos());
		initialMousePos.set(Vector2D(ih().getMousePos().first, ih().getMousePos().second));
		


		initialTransformPosWithOffSet.set(initialMousePos- Vector2D( card->getComponent<BoxCollider>()->getRect()->w /2 , card->getComponent<BoxCollider>()->getRect()->h/2 ));

	}

}

void DragManager::OnLeftClickUp()
{
	//si no tenemos carta drageada, no hacemos nada

	//si, si la tenemos, verificamos colisiones con el grupo DropDetector
	if (dragTransform != nullptr) {

		auto drop = mouseRaycast(ecs::grp::DROPS);

		auto dropDetector = ((drop != nullptr) ? drop->getComponent<DropDetector>() : nullptr);

		//si tenemos una colision con el drop detector, cambiamos la posicion de la carta por la que guarde el drop
		//también confirmamos que tenemos suficientes puntos de acción para lanzar la carta
		if (drop != nullptr && 
			!dropDetector->isOcuped() && enoughPoints(dragTransform->getEntity()))
		{
			
			playCardMultiplayer(dragTransform->getEntity(), dropDetector->getBoardPos());


			putCardAnimation(dropDetector);
			
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

		//Quitamos el feedback de colocar la carta
		if (drop != nullptr) drop->getComponent<ShineComponent>()->outShine();
		//en cualquier caso, ya no tenemos carta drageada
		dragTransform = nullptr;
		//Quitamos todo el feedback del tablero
		boardManager->returnColors();
	}

}

void DragManager::putCardAnimation(DropDetector* cell)
{
	//colocar la carta en su sitio(posicion en la pantalla)
	dragTransform->setGlobalPos(cell->getCardPos());

}

bool DragManager::CardOnHand(ecs::entity_t card)
{
	return card->getComponent<CardStateManager>()->getState() == Cards::ON_HAND;
}


//returns true if card is belongs to the player who have the turn
bool DragManager::CardIsOfCurrentPlayer(ecs::entity_t card)
{
	const auto matchManager = mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>();

	const Players::Owner turnOwner =
		matchManager->getActualState() == Turns::J1 ? Players::PLAYER1 :
		matchManager->getActualState() == Turns::J2 ? Players::PLAYER2 :
		Players::NONE;

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

	// AQUI



	ecs::entity_t ent = GameStateMachine::instance()->getMngr()->getHandler(ecs::hdlr::TUTORIAL_MANAGER);
	if (ent != nullptr && ent->hasComponent<TutorialManager>()) {

		// handler del tutorial para tocar el action done
		ent->getComponent<TutorialManager>()->tutorialActionEnded(Tutorials::Tutorials::BOARD, Tutorials::Board::PLACE_CARD);
		//ent->getComponent<TutorialManager>()->tutorialActionEnded(Tutorials::Tutorials::BOARD, Tutorials::Board::NEXT_CARD_1);
	}
	
}

void DragManager::colorEffects(ecs::entity_t drop)
{
	auto c = dragTransform->getEntity()->getComponent<Card>();	//Carta draggeada

	//Buscamos la carta por su ID
	auto id = c->getID();
	auto l = sdlutils().cards().at(std::to_string(id));

	auto cell = drop->getComponent<Cell>();	//Celda sobre la que está la carta

	//Valor original de las cartas
	auto v = 0;

	//Miramos todos los efectos que tenga la carta
	for (auto e : l.effects()) {

		//Diferenciamos los diferentes tipos de efectos que nos interesa
		switch (e.type()) {
		case Effects::Superflecha:
			for (auto d : e.directions()) {

				while (cell != nullptr)	//Pintamos toda la fila
				{
					cell->getEntity()->getComponent<SpriteRenderer>()->setMultiplyColor(85, 100, 235, 255);

					//Cambiar aquí los números??
					/*auto cardEffect = cell->getCard();
					if (cardEffect != nullptr) {
						v = cardEffect->getValue();

						cardEffect->setValue(e.value() + v);
					}*/
					cell = cell->getAdjacents()[d];		//Hace que miremos la celda ayacente
					//cardEffect->setValue(v);

				}
			}
			break;

		case Effects::Flecha:

			for (auto d : e.directions()) {

				if (cell->getAdjacents()[d] != nullptr)	//Solo pintamos la correspondiente
				{
					
					cell->getEntity()->getComponent<SpriteRenderer>()->setMultiplyColor(85, 100, 235, 255);
					cell = cell->getAdjacents()[d];		//Hace que miremos la celda ayacente
					//Cambiar aquí los números??
					cell->getEntity()->getComponent<SpriteRenderer>()->setMultiplyColor(85, 100, 235, 255);
				}
			}
			break;

		case Effects::Esquina:
			if (cell->getCorner()) {
				cell->getEntity()->getComponent<SpriteRenderer>()->setMultiplyColor(85, 100, 235, 255);
				//Con esto sería en la propia carta
			}
			break;

		case Effects::Centro:
			if (cell->getCenter()) {
				cell->getEntity()->getComponent<SpriteRenderer>()->setMultiplyColor(85, 100, 235, 255);
				//Aquí tambien sería en la propia carta
			}
			break;
		}
	}
}


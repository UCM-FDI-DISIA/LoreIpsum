#include "pch.h"
#include "PizarraManager.h"
#include "../../Data.h"
#include "../../GameStateMachine.h"
#include "../../gamestates/GameState.h"
#include "Manager.h"
#include "../Card.h"

PizarraManager::PizarraManager() {}

PizarraManager::~PizarraManager() {}

// ---- Metodos heredados (no es TAAAAAAAAN importante) ----
void PizarraManager::update() {}

void PizarraManager::initComponent()
{
	// guarda en un array aux las cartas que ya estuvieran en la pizarra
	for (auto e : GameStateMachine::instance()->getCurrentState()->getMaze()) {
		if (isOnPizarra(e.first)) {

			mazeaux.push_back(e.first);
			mazePosaux.push_back(e.second);

		}
	}

	// limpia el mazo que vas a sobreescribir entero
	mazePrev.clear();
	mazePos.clear();

	// aniade las que ya tenias en la pizarra
	for (auto e : mazeaux) {
		mazePrev.push_back(e);
	}

	// aniade las que ya tenias en la pizarra
	for (auto e : mazePosaux) {
		mazePosaux.push_back(e);
	}

	// aniade las nuevas
	for (auto e : GameStateMachine::instance()->getCurrentState()->getMaze()) {
		if (!isOnPizarra(e.first)) {

			mazePrev.push_back(e.first);
			mazePos.push_back(e.second);
		}
	}

	auto itPos = mazePos.begin();

	// instancia las cartas de tu mazo
	for (auto e : mazePrev)
	{
		Transform* card;
		card = GameStateMachine::instance()->getCurrentState()->createCard(e, (*itPos))->getComponent<Transform>();

		cards.push_back(card);
		itPos++;
	}
}

void PizarraManager::refreshPos()
{

}

// ---- Manageo pa cosas fuera de la pizarra ----
// Guarda el mazo en el data.
void PizarraManager::saveMaze()
{
	mazePos.clear();

	for (auto e : cards)
	{
		if (e != nullptr)
		{
			mazePos.push_back(e->getGlobalPos());
		}
	}

	GameStateMachine::instance()->getCurrentState()->setMaze(mazePrev, mazePos);
	TuVieja("saveMaze");
}

// Devuelve true si la carta (id) esta en la pizarra.
bool PizarraManager::isOnPizarra(int id)
{
	bool encontrado = false;
	for (auto e : mazePrev) {
		if (id == e) {
			encontrado = true;
		}
	}

	return encontrado;
}

bool PizarraManager::isPizarraLlena()
{
	// si el tamanio del mazo provisional llega el tamanio max
	return mazePrev.size() >= MAX_CARDS_MAZE;
}

// ---- Manageo de cartas en la pizarra ----
// Aniade carta a la pizarra.
void PizarraManager::addCard(int id, Transform* card)
{
	// si la carta no estaba ya en la pizarra
	if (!isOnPizarra(id)) {
		// se aniade
		mazePrev.push_back(id);
		// se aniade Posicion
		cards.push_back(card);

		// aumenta el contador
		cantCards++;
	}
}

// Quita carta de la pizarra.
void PizarraManager::removeCard(int id)
{
	// guarda en un iterador la posicion de la carta que se busca
	std::list<int>::iterator find = std::find(mazePrev.begin(), mazePrev.end(), id);

	// borra lo que haya en la pos que hayas guardado
	mazePrev.erase(find);

	auto it = cards.begin();

	bool encontrado = false;
	while (!encontrado && it != cards.end() )
	{
		if ((*it)->getEntity()->getComponent<Card>()->getID() == id)
		{
			cards.erase(it);
			encontrado = true;
		}
		else
		{
			it++;

		}
	}

	// disminuye el contador
	cantCards--;
}
#include "pch.h"
#include "PizarraManager.h"
#include "../../Data.h"
#include "../../GameStateMachine.h"
#include "../../gamestates/GameState.h"

PizarraManager::PizarraManager() {}

PizarraManager::~PizarraManager() {}

// ---- Metodos heredados (no es TAAAAAAAAN importante) ----
void PizarraManager::update() {}

void PizarraManager::initComponent()
{
	// guarda en un array aux las cartas que ya estuvieran en la pizarra
	for (auto e : GameStateMachine::instance()->getCurrentState()->getMaze()) {
		if (isOnPizarra(e)) {

			mazeaux.push_back(e);
		}
	}

	// limpia el mazo que vas a sobreescribir entero
	mazePrev.clear();

	// aniade las que ya tenias en la pizarra
	for (auto e : mazeaux) {
		mazePrev.push_back(e);
	}

	// aniade las nuevas
	for (auto e : GameStateMachine::instance()->getCurrentState()->getMaze()) {
		if (!isOnPizarra(e)) {

			mazePrev.push_back(e);
		}
	}

	// instancia las cartas de tu mazo
	for (auto e : mazePrev)
	{
		GameStateMachine::instance()->getCurrentState()->createCard(e, Vector2D(25, 300));
	}
}

// ---- Manageo pa cosas fuera de la pizarra ----
// Guarda el mazo en el data.
void PizarraManager::saveMaze()
{
	GameStateMachine::instance()->getCurrentState()->setMaze(mazePrev);
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
void PizarraManager::addCard(int id)
{
	// si la carta no estaba ya en la pizarra
	if (!isOnPizarra(id)) {
		// se aniade
		mazePrev.push_back(id);

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

	// disminuye el contador
	cantCards--;
}
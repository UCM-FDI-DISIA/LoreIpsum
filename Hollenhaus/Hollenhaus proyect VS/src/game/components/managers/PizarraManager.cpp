#include "pch.h"
#include "PizarraManager.h"
#include "../../Data.h"
#include "../../GameStateMachine.h"
#include "../../gamestates/GameState.h"

PizarraManager::PizarraManager()
{

}
PizarraManager::~PizarraManager()
{

}

// ---- Metodos heredados (no es TAAAAAAAAN importante) ----
void PizarraManager::update()
{

}
void PizarraManager::initComponent()
{
	for (auto e : GameStateMachine::instance()->getCurrentState()->getMaze()) {
		if (isOnPizarra(e)) {

			mazeaux.push_back(e);
		}
	}
	mazePrev.clear();

	for (auto e : mazeaux) {
		mazePrev.push_back(e);
	}

	for (auto e : GameStateMachine::instance()->getCurrentState()->getMaze()) {
		if (!isOnPizarra(e)) {

			mazePrev.push_back(e);
		}
	}

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
	pizarraLlena = mazePrev.size() >= MAX_CARDS_MAZE;
	return pizarraLlena;
}

// ---- Manageo de cartas en la pizarra ----
// Aniade carta a la pizarra.
void PizarraManager::addCard(int id)
{
	if (!isOnPizarra(id)) {
		mazePrev.push_back(id);
		cantCards++;
	}
}

// Quita carta de la pizarra.
void PizarraManager::removeCard(int id)
{
	std::list<int>::iterator find = std::find(mazePrev.begin(), mazePrev.end(), id);

	//mazePrev.remove(id);
	mazePrev.erase(find);
	cantCards--;
}
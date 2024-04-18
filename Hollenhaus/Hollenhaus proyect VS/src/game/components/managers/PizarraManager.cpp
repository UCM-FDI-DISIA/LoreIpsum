#include "pch.h"
#include "PizarraManager.h"
#include "../../Data.h"
#include "../../GameStateMachine.h"
#include "../../gamestates/GameState.h"
#include "Manager.h"
#include "../Card.h"

PizarraManager::PizarraManager()
{
}

PizarraManager::~PizarraManager()
{
}

// ---- Metodos heredados ----
void PizarraManager::update()
{
}

void PizarraManager::initComponent()
{
	// guarda en un array aux las cartas que ya estuvieran en la pizarra
	// recorre cada pair del map mazo de data
	for (auto e : GameStateMachine::instance()->getCurrentState()->getMaze())
	{
		// si la primera componente de la pareja (id) ya estaba en la pizarra
		if (isOnPizarra(e.first))
		{
			// guardas el id
			mazeaux.push_back(e.first);

			// guardas la pos
			mazePosaux.push_back(e.second);
		}
	}

	// limpia el mazo que vas a sobreescribir entero
	mazePrev.clear();
	mazePos.clear();

	// aniade las que ya tenias en la pizarra (id)
	for (auto e : mazeaux)
	{
		mazePrev.push_back(e);
	}

	// aniade las que ya tenias en la pizarra (pos)
	for (auto e : mazePosaux)
	{
		mazePosaux.push_back(e);
	}

	// aniade las nuevas
	for (auto e : GameStateMachine::instance()->getCurrentState()->getMaze())
	{
		// si la primera componente de la pareja (id) NO estaba en la pizarra
		if (!isOnPizarra(e.first))
		{
			// guardas el id
			mazePrev.push_back(e.first);

			// guardas la pos
			mazePos.push_back(e.second);
		}
	}

	// iterador al inicio de la lista de pos (indice)
	auto itPos = mazePos.begin();

	// recorres el mazo
	for (auto e : mazePrev)
	{
		// instancia las cartas de tu mazo
		Transform* card;
		card = GameStateMachine::instance()->getCurrentState()->createCard(e, (*itPos))->getComponent<Transform>();
		cards.push_back(card);

		// recorres la lista de pos
		++itPos;
	}

	cantCards = mazePrev.size();
}

// ---- Manageo pa cosas fuera de la pizarra ----
// Guarda el mazo en el data.
void PizarraManager::saveMaze()
{
	if (mazePrev.size() >= MIN_CARDS_MAZE && mazePrev.size() <= MAX_CARDS_MAZE)
	{
		// limpias mazo de pos
		mazePos.clear();

		// recorres las cartas en pizarra
		for (auto e : cards)
		{
			// si existe la entidad
			if (e != nullptr)
			{
				// guardas su pos en la lista de pos de cartas en pizarra
				mazePos.push_back(e->getGlobalPos());
			}
		}

		// guardas el mazo pasando las listas de id y pos
		GameStateMachine::instance()->getCurrentState()->setMaze(mazePrev, mazePos);

		// DEBUG
		TuVieja("saveMaze");
	}
	else
	{
		// No hay las suficientes cartas
		TuVieja("noGuardado");
	}
}

// Devuelve true si la carta (id) esta en la pizarra.
bool PizarraManager::isOnPizarra(int id)
{
	bool encontrado = false;
	for (auto e : mazePrev)
	{
		if (id == e)
		{
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
	if (!isOnPizarra(id))
	{
		// se aniade id
		mazePrev.push_back(id);

		// se aniade pos
		cards.push_back(card);

		// aumenta el contador de cartas en pizarra
		cantCards++;
	}
}

// Quita carta de la pizarra.
void PizarraManager::removeCard(int id)
{
	// guarda en un iterador la posicion de la carta que se busca
	auto find = std::find(mazePrev.begin(), mazePrev.end(), id);

	// borra lo que haya en la pos que hayas guardado
	mazePrev.erase(find);

	// iterador al inicio de la lista de pos (indice)
	auto it = cards.begin();

	bool encontrado = false;

	// mientras no lo hayas encontrado y queden entidades
	while (!encontrado && it != cards.end())
	{
		// si la encuentras se borra
		if ((*it)->getEntity()->getComponent<Card>()->getID() == id)
		{
			cards.erase(it);
			encontrado = true;
		}

		// si no, seguimos buscando
		else
		{
			++it;
		}
	}

	// disminuye el contador (resta una carta de la pizarra)
	cantCards--;
}

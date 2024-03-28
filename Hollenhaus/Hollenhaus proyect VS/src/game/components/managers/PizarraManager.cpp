#include "pch.h"
#include "PizarraManager.h"
#include "../../Data.h"

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

}

// ---- Manageo pa cosas fuera de la pizarra ----
// Guarda el mazo en el data.
void PizarraManager::saveMaze()
{
	TuVieja("saveMaze");
}

// Devuelve true si la carta (id) esta en la pizarra.
bool PizarraManager::isOnPizarra(int id)
{
	return true;
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
	mazePrev.push_back(id);
	cantCards++;
}

// Quita carta de la pizarra.
void PizarraManager::removeCard(int id)
{
	std::list<int>::iterator find = std::find(mazePrev.begin(), mazePrev.end(), id);

	//mazePrev.remove(id);
	mazePrev.erase(find);
	cantCards--;
}
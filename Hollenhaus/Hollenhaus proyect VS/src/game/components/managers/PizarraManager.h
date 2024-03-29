#pragma once
#include "../ComponentUpdate.h"
#include "../../ecs.h"
#include <list>

class Data;

class PizarraManager : public ComponentUpdate
{
private:
	// Mazo en la pizarra
	std::list<int> mazePrev;
	// Auxiliar para el guardado del mazo
	std::list<int> mazeaux;

	// lista de entidades cartas en la pizarra
	std::list<ecs::entity_t> cards;

	// Cantidad de cartas en el mazo
	int cantCards;

public:
	// ---- Constructora/Destructora ----
	PizarraManager();
	~PizarraManager();

	// ---- Metodos heredados (no es TAAAAAAAAN importante) ----
	void update() override;
	void initComponent() override;

	// ---- Manageo pa cosas fuera de la pizarra ----
	// Guarda el mazo en el data.
	void saveMaze();

	// Devuelve true si la carta (id) esta en la pizarra.
	bool isOnPizarra(int id);

	// Devuelve true si la pizarra esta llena
	bool isPizarraLlena();

	// ---- Manageo de cartas en la pizarra ----
	// Aniade carta a la pizarra.
	void addCard(int id);

	// Quita carta de la pizarra.
	void removeCard(int id);
};

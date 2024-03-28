#pragma once
#include "../ComponentUpdate.h"
#include <list>

class Data;

class PizarraManager : public ComponentUpdate
{
private:
	std::list<int> mazePrev;
	int cantCards;
	bool pizarraLlena;

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

	bool isPizarraLlena();

	// ---- Manageo de cartas en la pizarra ----
	// Aniade carta a la pizarra.
	void addCard(int id);

	// Quita carta de la pizarra.
	void removeCard(int id);
};

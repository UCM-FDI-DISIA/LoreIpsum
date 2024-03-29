#pragma once
#include "../ComponentUpdate.h"
#include "../../Data.h"
#include "../../ecs.h"
#include <array>

const int CANT_CARTAS_MOSTRADAS_CAJON = 6;
class DrawerManager : public ComponentUpdate
{
private:
	std::array<int, CARDS_IN_GAME> drawer;

	// lleva la cuenta de en que cajon estamos
	int cajonesAbiertos;

	// Array auxiliar para guardar las cartas actuales del cajon
	std::array<ecs::entity_t, CANT_CARTAS_MOSTRADAS_CAJON> cardsAux;

	// ---- Manageos externos ----
	// crea las cartas del cajon en un rango
	void refreshPos();

public:
	// ---- Constructora/Destructora ----
	DrawerManager();
	~DrawerManager();

	// ---- Metodos heredados (no es TAAAAAAAAN importante) ----
	void update() override;
	void initComponent() override;

	void saveDrawer();

	bool isOnDrawer(int id);

	// ---- Manageos de carta ----
	// Aniade carta
	void addCard(int id);

	// Quita carta
	void removeCard(int id);

	// ---- Manageos de botones ----
	// muestra las siguientes n cartas
	void drawerPalante();

	// muestra las anteriores n cartas
	void drawerPatras();

};


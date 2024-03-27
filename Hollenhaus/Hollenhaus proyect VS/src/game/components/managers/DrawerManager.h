#pragma once
#include "../ComponentUpdate.h"

const int CANT_CARTAS_MOSTRADAS_DB = 6;
class DrawerManager : public ComponentUpdate
{
private:
	// lleva la cuenta de en que cajon estamos
	int cajonesAbiertos;

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


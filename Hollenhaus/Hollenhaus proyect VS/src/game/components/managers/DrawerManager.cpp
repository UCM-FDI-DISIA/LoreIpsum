#include "pch.h"
#include "DrawerManager.h"
#include "../../GameStateMachine.h"
#include "../../gamestates/GameState.h"


DrawerManager::DrawerManager() : cajonesAbiertos(0),
drawer(GameStateMachine::instance()->getCurrentState()->getDrawer())
{
}

DrawerManager::~DrawerManager()
{
}

void DrawerManager::refreshPos()
{
	for (int i = 0; i < CANT_CARTAS_MOSTRADAS_CAJON; i++)
	{
		if (cardsAux[i] != nullptr) {
			cardsAux[i]->setAlive(false);
		}
	}
	

	for (int i = CANT_CARTAS_MOSTRADAS_CAJON * cajonesAbiertos; i < CANT_CARTAS_MOSTRADAS_CAJON; i += CANT_CARTAS_MOSTRADAS_CAJON)
	{
		if (drawer[i] != -1)
		{
			cardsAux[i] = GameStateMachine::instance()->getCurrentState()->createCard(drawer[i], Vector2D(25 * i, 100));
		}
	}
}

void DrawerManager::update()
{
}

void DrawerManager::initComponent()
{
	refreshPos();
}

void DrawerManager::saveDrawer()
{
	GameStateMachine::instance()->getCurrentState()->setDrawer(drawer);
}

bool DrawerManager::isOnDrawer(int id)
{
	return drawer[id] == id;
}

void DrawerManager::addCard(int id)
{
	drawer[id] = id;
	std::cout << drawer[id] << std::endl;
}

void DrawerManager::removeCard(int id)
{
	drawer[id] = -1;
	std::cout << drawer[id] << std::endl;
}

void DrawerManager::drawerPalante()
{
	TuVieja("drawerPalante");
	if (cajonesAbiertos < CARDS_IN_GAME / CANT_CARTAS_MOSTRADAS_CAJON)
	{
		cajonesAbiertos++;
	}
	refreshPos();
}

void DrawerManager::drawerPatras()
{
	TuVieja("drawerPatras");
	if (cajonesAbiertos > 0)
	{
		cajonesAbiertos--;
	}
	refreshPos();
}

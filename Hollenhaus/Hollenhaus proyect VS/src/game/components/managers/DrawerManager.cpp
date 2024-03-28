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
	for (int i = cajonesAbiertos; i < CANT_CARTAS_MOSTRADAS_DB; i++)
	{
		if (drawer[i] != -1)
		{
			GameStateMachine::instance()->getCurrentState()->createCard(drawer[i]);
		}
	}
}

void DrawerManager::update()
{
}

void DrawerManager::initComponent()
{
	
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
	refreshPos();
}

void DrawerManager::drawerPatras()
{
	TuVieja("drawerPatras");
}

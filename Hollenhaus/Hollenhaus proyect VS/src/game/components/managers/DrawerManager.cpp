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

void DrawerManager::update()
{
}

void DrawerManager::initComponent()
{
}

void DrawerManager::addCard(int id)
{
	std::cout << drawer[id] << std::endl;
}

void DrawerManager::removeCard(int id)
{

}

void DrawerManager::drawerPalante()
{
	TuVieja("drawerPalante");
}

void DrawerManager::drawerPatras()
{
	TuVieja("drawerPatras");
}

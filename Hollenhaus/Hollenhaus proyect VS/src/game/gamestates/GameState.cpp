#include <../pchs/pch.h>

#include "GameState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/Transform.h"
#include "../components/basics/SpriteRenderer.h"
#include "../../sdlutils/InputHandler.h"
#include "../GameStateMachine.h"
#include "../Data.h"

// factorias
#include "../factories/Factory.h"
#include "../factories/FakeCardFactory_v0.h"
#include "game/CaseManager.h"

// DECLARAR LAS VARIABLES ESTATICAS
Data* GameState::data = nullptr;

//GameState::GameState()
//{
//
//    /*
//    auto mngr = GameStateMachine::instance()->getMngr();
//
//    auto entityPrueba = mngr->addEntity();
//    std::cout << ((mngr->getComponent<Transform>(entityPrueba)) != nullptr) << std::endl;
//    auto componentPrueba = mngr->addComponent<Transform>(entityPrueba);
//    std::cout << ((mngr->getComponent<Transform>(entityPrueba)) != nullptr) << std::endl;
//    //auto componentPrueba2 = mngr->addComponent<SpriteRenderer>(entityPrueba, "hola");
//    std::cout << ((mngr->hasComponent<Transform>(entityPrueba))) << std::endl;
//    std::cout << ((mngr->hasComponent<SpriteRenderer>(entityPrueba))) << std::endl;
//    */
//
//
//
//    //ih().insertFunction(0, [this] {PruebaInput(); });
//
//    //ih().insertFunction(InputHandler::MOUSE_LEFT_CLICK, [this] {PruebaInput(); });
//    //ih().clearFunction(InputHandler::MOUSE_LEFT_CLICK, [this] {PruebaInput(); });
//}

void GameState::newKey()
{
}

//borra todas las entidades
GameState::~GameState()
{
	GameStateMachine::instance()->getMngr()->Free();
}


//Su objetivo es borrar todas las entidades muertas, es
//decir las que han salido del juego en la �ltima iteraci�n
void GameState::refresh()
{
	GameStateMachine::instance()->getMngr()->refresh();
}


/**
* llama a tu padre
*/
void GameState::update()
{
	GameStateMachine::instance()->getMngr()->update();
}

void GameState::render() const
{
	GameStateMachine::instance()->getMngr()->render();
}

void GameState::setWinnerOnData(int w)
{
	data->setWinner(w);
}

void GameState::setLastPaulPos(Vector2D paulPos)
{
	data->SetCityPos(paulPos);
}

void GameState::setLastPaulDir(bool dir)
{
	data->setPaulDir(dir);
}

void GameState::nextCase()
{
	data->AddCaseIndex();
}

void GameState::setDefeatedNPC(int id)
{
	data->AddDefeatedNPC(id);
}

bool GameState::TUTORIAL_DECKBUILDING_COMPLETE()
{
	return data->getTUTORIAL_DECKBUILDING_COMPLETE();
}

void GameState::setTUTORIAL_DECKBUILDING_COMPLETE(bool a)
{
	data->setTUTORIAL_DECKBUILDING_COMPLETE(a);
}

bool GameState::TUTORIAL_CITY_COMPLETE()
{
	return data->getTUTORIAL_CITY_COMPLETE();
}

void GameState::setTUTORIAL_CITY_COMPLETE(bool a)
{
	data->setTUTORIAL_CITY_COMPLETE(a);
}

bool GameState::TUTORIAL_BOARD_COMPLETE()
{
	return data->getTUTORIAL_BATTLE_COMPLETE();
}

void GameState::setTUTORIAL_BOARD_COMPLETE(bool a)
{
	data->setTUTORIAL_BATTLE_COMPLETE(a);
}

bool GameState::TUTORIAL_SHOP_COMPLETE()
{
	return data->getTUTORIAL_SHOP_COMPLETE();
}

void GameState::setTUTORIAL_SHOP_COMPLETE(bool a)
{
	data->setTUTORIAL_SHOP_COMPLETE(a);
}

void GameState::setSocketRival(TCPsocket _rival)
{
	data->setSocketRival(_rival);
}

TCPsocket GameState::getSocketRival()
{
	return data->getSocketRival();
}

void GameState::resetSocketRival()
{
	data->resetSocketRival();
}

void GameState::setIsHost(bool b)
{
	data->setIsHost(b);
}

bool GameState::getIsHost()
{
	return data->getIsHost();
}

void GameState::setMazeRival(std::vector<int> mazeRival)
{
	data->SetNewMazeRival(mazeRival);
}

std::vector<int> GameState::getMazeRival()
{
	return data->GetMazeRival();
}

void GameState::SetLastState(int ls)
{
	data->setLastState(ls);
}

bool GameState::GetSaveExists()
{
	return data->SaveExists();
}

std::array<int, CARDS_IN_GAME> GameState::getDrawer()
{
	return data->GetDrawer();
}

// para acceder al mazo del data desde el estado
std::unordered_map<int, Vector2D> GameState::getMazeWithPos()
{
	return data->GetMazeWithPos();
}

// para acceder al mazo del data desde el estado
std::list<int> GameState::getMaze()
{
	return data->GetMaze();
}

Vector2D GameState::getLastPaulPos()
{
	return data->getLastPaulPos();
}

bool GameState::getLastPaulDir() const
{
	return data->getLastPaulDir();
}

int GameState::GetLastState()
{
	return data->getLastState();
}

int GameState::getLastDefeatedNPC()
{
	return data->getLastDefeatedNPC();
}

// para settear el mazo del data desde el estado
void GameState::setMaze(std::list<int> mazeToSave, std::list<Vector2D> MazePosToSave)
{
	data->SetNewMaze(mazeToSave, MazePosToSave);
}

void GameState::setDrawer(std::array<int, 50> drawerToSave)
{
	data->SetNewDrawer(drawerToSave);
}

void GameState::setKey()
{
}

void GameState::setJ2(std::string rival)
{
}

bool GameState::isDefeated(int i)
{
	return data->IdIsInDefeatedNPC(i);
}

void GameState::saveData()
{
	data->Write();
}

void GameState::loadData()
{
	data->Read();
}

void GameState::loadDataIfExists()
{
	if (GetSaveExists())
	{
		data->Read();
		GameStateMachine::instance()->caseMngr()->init();
	}
}

void GameState::newGameData()
{
	data->resetSave();
}

void GameState::resetShop()
{
	data->resetShopCards();
}

void GameState::setAccepted(bool b)
{
	data->setAccepted(b);
}

bool GameState::getAccepted()
{
	return data->getAccepted();
}

ecs::entity_t GameState::createCard(int id, Vector2D pos)
{
	// ---- CARDS ----
	Factory* factory = new Factory();
	factory->SetFactories(static_cast<FakeCardFactory*>(new FakeCardFactory_v0()));

	// Hace LA carta segun su id, en la pos que se pida
	auto card = sdlutils().cards().at(std::to_string(id));
	ecs::entity_t ent = factory->createFakeCard(id, pos, card.cost(), card.value(), card.sprite(), card.unblockable(), card.effects());
	return ent;
}

void GameState::setData(Data* _data)
{
	data = _data;
}

void GameState::setShopCard(int c)
{
	data->setShopCard(c);
}

bool GameState::checkDataShopCardsIsEmpty()
{
	return data->shopCardsIsEmpty();
}

bool GameState::checkCardIsInDrawer(int id)
{
	return data->IdIsInDrawer(id);
}

int GameState::getShopCardById(int id)
{
	return  data->getShopCardById(id);
}

void GameState::addCardToDrawer(int id)
{
	data->AddCardToDrawer(id);
}

void GameState::addMoney(int money)
{
	data->AddMoney(money);
}

void GameState::addKey()
{
	newKey();
	data->AddKey();
}

void GameState::substractMoney(int money)
{
	data->SubtractMoney(money);
}

int GameState::getMoney()
{
	return data->GetMoney();
}

int GameState::getSouls()
{
	return data->GetSouls();
}

int GameState::getKeys()
{
	return data->GetKeys();
}

bool GameState::checkCardIsInMaze(int id) {
	return data->IdIsInMaze(id);
}

int GameState::getCurrentCase()
{
	return data->GetCurrentCase();
}



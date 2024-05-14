#include <../pchs/pch.h>

#include "TutorialManager.h"
#include "../game/gamestates/TutorialBoardState.h"

TutorialManager::TutorialManager() : ended(false)
{


}

TutorialManager::~TutorialManager()
{
}

void TutorialManager::initComponent()
{

	count = 0;
	cooldown = 10;

	resetAction();

	//actionEnded();
	//ended = true;

	isTutorial = false;


	
}

void TutorialManager::update()
{
}

void TutorialManager::actionEnded()
{
	ended = true;

}

void TutorialManager::resetAction()
{
	ended = false;
}

void TutorialManager::wait(std::function<void()> callback)
{
	// tiempo de espera
	if (count < cooldown) {

		count++;
	}
	else {
		
		//
		callback();

		//
		count = 0;
	}
}

void TutorialManager::tutorialActionEnded(Tutorials::Tutorials t, int i)
{
	if (isTutorial && t == currtut && i == currstate && !ended) {

		actionEnded();
		// HERE
	}
}

void TutorialManager::setColliderWall(std::vector<ecs::entity_t> e, ecs::entity_t parent)
{

	colliderWall = Instantiate();

	// --------
	colliderWall->addComponent<Transform>();
	colliderWall->addComponent<SpriteRenderer>("oldWhiteRect");
	colliderWall->getComponent<Transform>()->addParent(parent->getComponent<Transform>());

	//dialogue->getComponent<Transform>()->getRelativeScale().set(scaleBox.getX(), scaleBox.getY()); //escala del whiteRect
	colliderWall->getComponent<Transform>()->getRelativeScale().set(10,10); //escala del whiteRect
	colliderWall->getComponent<Transform>()->setGlobalPos(0,0);

	colliderWall->getComponent<SpriteRenderer>()->setOpacity(80);
	
	colliderWall->setLayer(200);

	//colliderWall->getComponent<Transform>()->setGlobalPos({0, 0});

	// ajusta las capas de los objetos que quieres que se puedan clickar
	for (auto obj : e) {
		layers.push_back(obj->getLayer());
		obj->setLayer(200);
	}
}

void TutorialManager::resetColliderWall(std::vector<ecs::entity_t> e)
{

	if (layers.size() > 0) {

		int i = 0;
		// ajusta las capas de los objetos que quieres que se puedan clickar
		for (auto obj : e) {
			//layers.push_back(obj->getLayer());
			obj->setLayer(layers[i]);
			i++;
		}

	}
}

void TutorialManager::deactivateColliders(std::vector<ecs::entity_t> n)
{
	for (auto obj : n) {
		if (obj->hasComponent<BoxCollider>()) {
			loseCollider(obj->getComponent<BoxCollider>());
		}
	}
}

void TutorialManager::activateColliders(std::vector<ecs::entity_t> n)
{
	for (auto obj : n) {
		if (obj->hasComponent<BoxCollider>()) {
			returnCollider(obj->getComponent<BoxCollider>());
		}
		
	}
}

void TutorialManager::activateAllColliders()
{
	for (auto obj : objs) {
		if (obj->hasComponent<BoxCollider>()) {
			returnCollider(obj->getComponent<BoxCollider>());
		}
		
	}
}

void TutorialManager::setLayers(std::vector<ecs::entity_t> n)
{
	layers.clear();
	for (auto obj : n) {
		layers.push_back(obj->getLayer());
	}
}

void TutorialManager::loseCollider(BoxCollider* coll)
{
	coll->setPosOffset({ 10000, 1000});
}

void TutorialManager::returnCollider(BoxCollider* coll)
{
	coll->setPosOffset({0,0});
}

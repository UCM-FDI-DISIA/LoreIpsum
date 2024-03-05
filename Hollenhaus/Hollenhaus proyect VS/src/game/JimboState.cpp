#include "JimboState.h"

#include "Entity.h"
#include "GameStateMachine.h"
#include "Manager.h"

#include "Transform.h"
#include "KeyManager.h"

JimboState::JimboState() : GameState() {
	
}

JimboState::~JimboState() {
}

void 
JimboState::refresh() {
	GameState::refresh();
}

void 
JimboState::update() {
	GameState::update();
}

void 
JimboState::render() const {
	GameState::render();
}

void 
JimboState::onEnter() {
	legend_ = Instantiate(Vector2D(0, 0));
	e_ = Instantiate();
	aa_ = Instantiate();

	legend_->addComponent<Transform>();
	e_->addComponent<Transform>();
	aa_->addComponent<Transform>();

	e_->getComponent<Transform>()->addParent(legend_->getComponent<Transform>());
	aa_->getComponent<Transform>()->addParent(legend_->getComponent<Transform>());

	e_->getComponent<Transform>()->removeParent();
	/*legend_->addComponent<KeyManager>()->initComponent();
	legend_->addComponent<SpriteRenderer>("key")->initComponent();
	legend_->getComponent<KeyManager>()->addKey("picto1");*/
}

void 
JimboState::onExit() {

}

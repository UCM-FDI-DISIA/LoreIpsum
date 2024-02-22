#include "JimboState.h"

#include "Entity.h"
#include "GameStateMachine.h"
#include "Manager.h"

#include "../Transform.h"

JimboState::JimboState() : GameState() {
	auto mngr = GameStateMachine::instance()->getMngr();

	card_ = mngr->addEntity();
	card2_ = mngr->addEntity();
	
	mngr->addComponent<Transform>(card_);
	mngr->addComponent<Transform>(card2_);

	transform = mngr->getComponent<Transform>(card_);
	transform2 = mngr->getComponent<Transform>(card2_);
	transform->getRelativePos().set(1, 1);
	//transform->getRelativePos().set(1, 1);

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
	std::cout << "GLOBAL: " << transform->getGlobalPos() << std::endl;
	std::cout << "RELATIVA: " << transform->getRelativePos() << std::endl;
}

void 
JimboState::render() const {
	GameState::render();
}

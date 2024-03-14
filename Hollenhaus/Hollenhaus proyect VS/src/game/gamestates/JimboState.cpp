#include "pch.h"
#include "JimboState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/Transform.h"
#include "../components/managers/KeyManager.h"
#include "../components/basics/SpriteRenderer.h"

JimboState::JimboState() : GameState() {
	legend_ = Instantiate(Vector2D(0, 0));

	legend_->addComponent<Transform>();
	legend_->addComponent<KeyManager>()->initComponent();
	legend_->addComponent<SpriteRenderer>("key")->initComponent();
	legend_->getComponent<KeyManager>()->addKey("picto1");
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
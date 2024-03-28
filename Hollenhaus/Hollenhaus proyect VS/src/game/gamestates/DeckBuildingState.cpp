// pch
#include "pch.h"

// estado
#include "DeckBuildingState.h"

// managers
#include "../components/managers/Manager.h"
#include "../components/DropZone.h"
#include "../components/DragNoCombat.h"

// factorias
#include "../factories/Factory.h"
#include "../factories/FakeCardFactory_v0.h"

// input
#include "../../sdlutils/InputHandler.h"

// componentes
#include "../components/basics/TextComponent.h"
#include "../components/NPC.h"

// ------------------------------------------------------- //

// ---- constructora ----
DeckBuildingState::DeckBuildingState()
{
	TuVieja("Loading DeckBuildingState");
}

// ---- basicos ----
void DeckBuildingState::update()
{
	GameState::update();
}

void DeckBuildingState::render() const
{
	GameState::render();
}

void DeckBuildingState::refresh()
{
	GameState::refresh();
}

// ---- ENTER ESTADO ----
void DeckBuildingState::onEnter()
{
	std::cout << "\nENTER DECKBUILDING.\n";

	// ---- DRAG ----
	// DragNoCombat se encarga de gestionar el drag de todas las cartas
	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragNoCombat>();

	// ---- CARDS ----
	auto card = sdlutils().cards().at(std::to_string(0));
	Factory* factory = new Factory();
	factory->SetFactories(static_cast<FakeCardFactory*>(new FakeCardFactory_v0()));
	Card* carda = factory->createFakeCard(0, Vector2D(100,100), card.cost(), card.value(), card.sprite(), card.unblockable(), card.effects())->getComponent<Card>();

	// ---- TEXTO ----
	ecs::entity_t officeText = Instantiate(Vector2D(210, 30));
	officeText->addComponent<TextComponent>("DECKBUILDING", "8bit_24pt", SDL_Color({ 255, 255, 255, 255 }), 350, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	officeText->setLayer(1);

	// ---- FONDO ----
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("rice");
	fondo->getComponent<Transform>()->getGlobalScale().set(0.85f, 0.85f);
	fondo->setLayer(0);

	// ---- BOTONES ----
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(2); // Lleva a la ciudad (1).
	exit->setLayer(1);

	// ---- PIZARRA ----
	ecs::entity_t pizarra = Instantiate();
	pizarra->addComponent<Transform>();
	pizarra->addComponent<SpriteRenderer>("black_box");
	pizarra->addComponent<BoxCollider>();
	pizarra->addComponent<PizarraManager>();
	pizarra->addComponent<DropZone>();
	pizarra->getComponent<DropZone>()->setCallBack([this](Card* card) { moveToPizarra(card); });
	Vector2D pizarraPos(300, 10);
	pizarra->getComponent<Transform>()->setGlobalPos(pizarraPos);
	pizarra->getComponent<Transform>()->setGlobalScale(4.5,3);
	pizarra->getComponent<BoxCollider>()->setAnchoredToSprite(true);

	// ---- CAJON ----


	// ---- SONIDO ----
	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("deckbuilder_theme").play(-1);
	sdl.soundEffects().at("deckbuilder_theme").setChannelVolume(10);
}

// ---- EXIT ESTADO ----
void DeckBuildingState::onExit()
{
	// ---- SONIDO ----
	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("deckbuilder_theme").pauseChannel();

	GameStateMachine::instance()->getMngr()->Free();

	std::cout << "\nEXIT DECKBUILDING.\n";
}

void DeckBuildingState::moveToPizarra(Card* card){
{
	drawer->removeCard(card->getID());
	pizarra->addCard(card->getID());
}}

void DeckBuildingState::moveToDrawer(Card* card)
{
	pizarra->removeCard(card->getID());
	drawer->addCard(card->getID());
}
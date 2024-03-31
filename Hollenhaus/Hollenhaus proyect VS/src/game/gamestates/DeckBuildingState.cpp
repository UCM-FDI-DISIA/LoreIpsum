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
#include "../components/Button.h"
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

	loadData();
	
	// ---- DRAG ----
	// DragNoCombat se encarga de gestionar el drag de todas las cartas
	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragNoCombat>();

	// ---- CARDS ----
	factory = new Factory();
	factory->SetFactories(static_cast<FakeCardFactory*>(new FakeCardFactory_v0()));
	//
	////hace la carta 1
	//auto card1 = sdlutils().cards().at(std::to_string(1));
	//factory->createFakeCard(1, Vector2D(100, 100), card1.cost(), card1.value(), card1.sprite(), card1.unblockable(), card1.effects())->getComponent<Card>();

	// ---- TEXTO ----
	ecs::entity_t officeText = Instantiate(Vector2D(210, 30));
	officeText->addComponent<TextComponent>("DECKBUILDING", "8bit_24pt", SDL_Color({ 255, 255, 255, 255 }), 350, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	officeText->setLayer(1);

	// ---- FONDO ----
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("DeckbuildingBG");
	fondo->getComponent<Transform>()->setGlobalScale(0.85f, 0.85f);
	//fondo->getComponent<Transform>()->getGlobalScale().set(0.85f, 0.85f);
	fondo->setLayer(0);

	// ---- BOTONES ----
	// ---- Salir:
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(2); // Lleva a la oficina (2).
	exit->setLayer(1);

	// ---- Confirmar Mazo:
	Vector2D botScale(.25f, .25f);
	ecs::entity_t Confirm = Instantiate();
	Confirm->addComponent<Transform>();
	Confirm->addComponent<SpriteRenderer>("boton_ph");
	Confirm->addComponent<BoxCollider>();
	Vector2D ConfirmPos(260, 330);
	Confirm->getComponent<Transform>()->setGlobalPos(ConfirmPos);
	Confirm->getComponent<Transform>()->setGlobalScale(botScale);
	Confirm->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	Confirm->addComponent<Button>();
	Confirm->getComponent<Button>()->connectToButton([this]() { pizarra_->saveMaze(); });
	Confirm->getComponent<Button>()->connectToButton([this]() { drawer_->saveDrawer(); });
	Confirm->setLayer(1);

	// Escalado de las flechas del drawer
	// ---- Pasar cajon alante:
	ecs::entity_t botPalante = Instantiate();
	botPalante->addComponent<Transform>();
	botPalante->addComponent<SpriteRenderer>("boton_ph");
	botPalante->addComponent<BoxCollider>();
	Vector2D botPalantePos(750, 420);
	botPalante->getComponent<Transform>()->setGlobalPos(botPalantePos);
	botPalante->getComponent<Transform>()->setGlobalScale(botScale);
	botPalante->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	botPalante->addComponent<Button>();
	botPalante->getComponent<Button>()->connectToButton([this]() { drawer_->drawerPalante(); });
	botPalante->setLayer(1);
	// ---- Pasar cajon atras:
	ecs::entity_t botPatras = Instantiate();
	botPatras->addComponent<Transform>();
	botPatras->addComponent<SpriteRenderer>("boton_ph");
	botPatras->addComponent<BoxCollider>();
	Vector2D botPatrasPos(750, 500);
	botPatras->getComponent<Transform>()->setGlobalPos(botPatrasPos);
	botPatras->getComponent<Transform>()->setGlobalScale(botScale);
	botPatras->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	botPatras->addComponent<Button>();
	botPatras->getComponent<Button>()->connectToButton([this]() { drawer_->drawerPatras(); });
	botPatras->setLayer(1);

	// ---- PIZARRA ----
	Vector2D pizarraPos(260, 40);
	ecs::entity_t pizarra = Instantiate(pizarraPos, ecs::grp::DROPZONE);
	pizarra->addComponent<Transform>();
	pizarra->addComponent<SpriteRenderer>("black_box");
	pizarra->addComponent<BoxCollider>();
	pizarra->addComponent<PizarraManager>();
	pizarra->addComponent<DropZone>();
	pizarra->getComponent<DropZone>()->setCallBack([this](Card* card) { moveToPizarra(card); });
	pizarra->getComponent<Transform>()->setGlobalPos(pizarraPos);
	pizarra->getComponent<Transform>()->setGlobalScale(4.5, 3.5);
	pizarra->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	pizarra_ = pizarra->getComponent<PizarraManager>();

	// ---- CAJON ----
	#pragma region CAJON
	Vector2D cajonPos(375, 400);
	ecs::entity_t cajon = Instantiate(cajonPos, ecs::grp::DROPZONE);
	cajon->addComponent<Transform>();
	cajon->addComponent<SpriteRenderer>("black_box");
	cajon->addComponent<BoxCollider>();
	cajon->addComponent<DrawerManager>();
	cajon->addComponent<DropZone>();
	cajon->getComponent<DropZone>()->setCallBack([this](Card* card) { moveToDrawer(card); });
	cajon->getComponent<Transform>()->setGlobalPos(cajonPos);
	cajon->getComponent<Transform>()->setGlobalScale(3.7f, 1.5f);
	cajon->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	drawer_ = cajon->getComponent<DrawerManager>();

	// ---- SONIDO ----
	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("deckbuilder_theme").play(-1);
	sdl.soundEffects().at("deckbuilder_theme").setChannelVolume(10);
}

// ---- EXIT ESTADO ----
void DeckBuildingState::onExit()
{
	saveData();

	// ---- SONIDO ----
	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("deckbuilder_theme").pauseChannel();

	GameStateMachine::instance()->getMngr()->Free();

	std::cout << "\nEXIT DECKBUILDING.\n";
}

void DeckBuildingState::moveToPizarra(Card* card)
{
	//TuVieja("HOSTIA TIO QUE NO LO HE ENCHUFAO - to pizarra");
	drawer_->removeCard(card->getID());
	// se aniade a la pizarra
	pizarra_->addCard(card->getID(), card->getEntity()->getComponent<Transform>());
}

void DeckBuildingState::moveToDrawer(Card* card)
{
	//TuVieja("HOSTIA TIO QUE NO LO HE ENCHUFAO - to cajon");
	pizarra_->removeCard(card->getID());

	// se aniade al cajon
	drawer_->addCard(card->getID(), card->getEntity());
}

ecs::entity_t DeckBuildingState::createCard(int id, Vector2D pos)
{
	// Hace LA carta
	auto card = sdlutils().cards().at(std::to_string(id));
	ecs::entity_t ent = factory->createFakeCard(id, pos, card.cost(), card.value(), card.sprite(), card.unblockable(), card.effects());
	return ent;

}



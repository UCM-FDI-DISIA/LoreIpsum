#include <../pchs/pch.h>


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
#include "../TutorialManager.h"
#include "../components/managers/TutorialDeckBuildingManager.h"
#include "game/components/Clickable.h"
#include "game/components/ShineComponent.h"

// ------------------------------------------------------- //

// ---- constructora ----
DeckBuildingState::DeckBuildingState()
{
	TuVieja("Loading DeckBuildingState");
	isTutorial = false;
}

DeckBuildingState::DeckBuildingState(bool t)
{
	isTutorial = true;
}

// ---- basicos ----
void DeckBuildingState::update()
{
	GameState::update();

	std::string cardsInMaze = std::to_string(pizarra_->getCantCartds()) + " / " + std::to_string(MAX_CARDS_MAZE);

	cantCards_->setTxt(cardsInMaze);

	/// Feedback
	tweenFade.step(1);
	fbSaved->getComponent<TextComponent>()->setAlpha(tweenFade.peek());
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

	// llamada al input
	ih().insertFunction(ih().PAUSEKEY_DOWN, [this] { onPauseDB(); });
	paused = false;

	// carga el data
	loadData();

	// ---- DRAG ----
	// DragNoCombat se encarga de gestionar el drag de todas las cartas de la escena
	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragNoCombat>();

	// ---- CARDS ----
	factory = new Factory();
	factory->SetFactories(static_cast<FakeCardFactory*>(new FakeCardFactory_v0()));


	// Cantidad de cartas:
	ecs::entity_t cantCards = Instantiate(Vector2D(80, 90));
	cantCards_ = cantCards->addComponent<TextComponent>(
		"xx / xx", "space_grotesk_bold_24",
		Colors::PEARL_HOLLENHAUS, 70,
		Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	cantCards->setLayer(1);

	// ---- FONDO ----
	// ---- pizarra:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("DeckbuildingBG");
	fondo->getComponent<Transform>()->setGlobalScale(0.51f, 0.515f);
	fondo->setLayer(0);

	/*
	// ---- Mesa:
	ecs::entity_t mesa = Instantiate();
	mesa->addComponent<Transform>();
	mesa->addComponent<SpriteRenderer>("DeckbuildingMesaBG");
	Vector2D posMesa(0, 210);
	mesa->getComponent<Transform>()->setGlobalPos(posMesa);
	mesa->getComponent<Transform>()->setGlobalScale(0.45f, 0.45f);
	mesa->setLayer(4);*/

	// ---- Cajon:
	ecs::entity_t caj = Instantiate();
	caj->addComponent<Transform>();
	caj->addComponent<SpriteRenderer>("DeckbuildingCajonBG");
	Vector2D posCajon(200, 400);
	caj->getComponent<Transform>()->setGlobalPos(posCajon);
	caj->getComponent<Transform>()->setGlobalScale(0.35f, 0.25f);
	caj->setLayer(0);

	// ---- BOTONES ----
#pragma region BOTONES
	// ---- Salir:
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(2, 2);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(2); // Lleva a la oficina (2).
	exit->setLayer(2);
	exit->addComponent<Clickable>("boton_flecha", true);

	// ---- Confirmar Mazo:
	Vector2D botMazScale(0.51f, 0.51f);
	ecs::entity_t Confirm = Instantiate();
	auto confirmTrans = Confirm->addComponent<Transform>();
	confirmTrans->addParent(fondo->getComponent<Transform>());
	auto boxCol = Confirm->addComponent<BoxCollider>();
	boxCol->setSize(Vector2D(200, 200));
	Vector2D ConfirmPos(138, 452);
	Confirm->getComponent<Transform>()->setGlobalPos(ConfirmPos);
	Confirm->getComponent<Transform>()->setGlobalScale(botMazScale);
	Confirm->addComponent<Button>();
	Confirm->getComponent<Button>()->connectToButton([this]()
	{
		resetFade();
		pizarra_->saveMaze();
		drawer_->saveDrawer();

	});
	Confirm->setLayer(2);
	Confirm->addComponent<SpriteRenderer>("postit_guardar_mazo");
	auto shinePostit = Confirm->addComponent<ShineComponent>();
	shinePostit->addEnt(Confirm->getComponent<SpriteRenderer>(), "postit_guardar_mazo_brilli");


	// ---- Pasar cajon alante:
	Vector2D botScale(0.75, 0.75);
	int botX = 720;
	int botY = 470;
	int botSep = 60;
	ecs::entity_t botPalante = Instantiate();
	botPalante->addComponent<Transform>();
	botPalante->addComponent<SpriteRenderer>("UpDrawer");
	botPalante->addComponent<BoxCollider>();
	botPalante->addComponent<Clickable>("UpDrawer", true);
	Vector2D botPalantePos(botX, botY);
	botPalante->getComponent<Transform>()->setGlobalPos(botPalantePos);
	botPalante->getComponent<Transform>()->setGlobalScale(botScale);
	botPalante->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	botPalante->addComponent<Button>();
	botPalante->getComponent<Button>()->connectToButton([this]() { drawer_->drawerPalante(); });
	botPalante->setLayer(2);

	// ---- Pasar cajon atras:
	ecs::entity_t botPatras = Instantiate();
	botPatras->addComponent<Transform>();
	botPatras->addComponent<SpriteRenderer>("DownDrawer");
	botPatras->addComponent<BoxCollider>();
	botPatras->addComponent<Clickable>("DownDrawer", true);
	Vector2D botPatrasPos(botX, botY + botSep);
	botPatras->getComponent<Transform>()->setGlobalPos(botPatrasPos);
	botPatras->getComponent<Transform>()->setGlobalScale(botScale);
	botPatras->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	botPatras->addComponent<Button>();
	botPatras->getComponent<Button>()->connectToButton([this]() { drawer_->drawerPatras(); });
	botPatras->setLayer(2);
#pragma endregion

	// ---- PIZARRA ----
#pragma region PIZARRA
	Vector2D pizarraPos(120, 35);
	ecs::entity_t pizarra = Instantiate(pizarraPos, ecs::grp::DROPZONE);

	// componentes basicos
	pizarra->addComponent<Transform>();
	//pizarra->addComponent<SpriteRenderer>("black_box");
	auto pizCol = pizarra->addComponent<BoxCollider>();
	pizCol->setSize(Vector2D(140, 120));
	pizarra->addComponent<PizarraManager>();
	pizarra->getComponent<Transform>()->setGlobalPos(pizarraPos);
	pizarra->getComponent<Transform>()->setGlobalScale(4.5, 3.5);
	//pizarra->getComponent<BoxCollider>()->setAnchoredToSprite(true);

	// establece la pizarra como dropzone
	pizarra->addComponent<DropZone>();

	// suscribe a la dropzone al callback movetopizarra
	pizarra->getComponent<DropZone>()->setCallBack([this](Card* card) { moveToPizarra(card); });

	// lo guarda
	pizarra_ = pizarra->getComponent<PizarraManager>();
#pragma endregion

	// ---- CAJON ----
#pragma region CAJON
	Vector2D cajonPos(300, 450);
	ecs::entity_t cajon = Instantiate(cajonPos, ecs::grp::DROPZONE);

	// componentes basicos
	cajon->addComponent<Transform>();
	//cajon->addComponent<SpriteRenderer>("black_box");
	auto cajCol = cajon->addComponent<BoxCollider>();
	cajCol->setSize(Vector2D(110, 100));
	cajon->addComponent<DrawerManager>();
	cajon->getComponent<Transform>()->setGlobalPos(cajonPos);
	cajon->getComponent<Transform>()->setGlobalScale(3.7f, 1.5f);
	//cajon->getComponent<BoxCollider>()->setAnchoredToSprite(true);

	// establece la pizarra como dropzone
	cajon->addComponent<DropZone>();
	cajon->getComponent<DropZone>()->setCallBack([this](Card* card) { moveToDrawer(card); });

	// lo guarda
	drawer_ = cajon->getComponent<DrawerManager>();
#pragma endregion


	/// Feedback guardado
	fbSaved = Instantiate(Vector2D());
	auto fbTrans = fbSaved->getComponent<Transform>();
	fbTrans->setGlobalPos(10, sdlutils().height() - 20 - 10);
	fbSaved->addComponent<TextComponent>(
		"Mazo guardado", Fonts::GROTESK_32,
		Colors::PEARL_HOLLENHAUS, 350,
		Text::BoxPivotPoint::LeftCenter, Text::TextAlignment::Left
	);
	fbSaved->setLayer(10);

	tweenFade = // dummy declaration
		tweeny::from(0)
		.to(0)
		.during(30)
		.via(tweeny::easing::linear);


	setTutorial();

	// ---- SONIDO ----
	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("deckbuilder_theme").play(-1);
	sdl.soundEffects().at("deckbuilder_theme").setChannelVolume(10);
}

// ---- EXIT ESTADO ----
void DeckBuildingState::onExit()
{
	// se desuscribe al evento
	ih().clearFunction(ih().PAUSEKEY_DOWN, [this] { onPauseDB(); });
	paused = false;

	// al salir del estado guardas la info
	saveData();

	// ---- SONIDO ----
	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("deckbuilder_theme").pauseChannel();

	GameStateMachine::instance()->getMngr()->Free();

	std::cout << "\nEXIT DECKBUILDING.\n";

	delete factory;
}

void DeckBuildingState::onPauseDB()
{
	if (!paused)
	{
		paused = true;

		rice = Instantiate();
		rice->addComponent<Transform>();
		rice->addComponent<SpriteRenderer>("rice");
		rice->addComponent<BoxCollider>();
		Vector2D posRice(300, 300);
		rice->getComponent<Transform>()->setGlobalPos(posRice);
		rice->getComponent<Transform>()->setGlobalScale(0.5f, 0.4f);
		rice->getComponent<BoxCollider>()->setAnchoredToSprite(true);
		rice->setLayer(4);
	}
	else if (paused && rice != nullptr)
	{
		paused = false;
		rice->setAlive(false);
	}

	//SetLastState(9);
	//pizarra_->saveMaze();
	//drawer_->saveDrawer();
	//GameStateMachine::instance()->setState(17);
}

#pragma region DECKBUILDING
void DeckBuildingState::moveToPizarra(Card* card)
{
	//TuVieja("HOSTIA TIO QUE NO LO HE ENCHUFAO - to pizarra");

	// ---- al mover una carta a la pizarra:
	// se elimina del cajon
	drawer_->removeCard(card->getID());

	// se aniade a la pizarra
	pizarra_->addCard(card->getID(), card->getEntity()->getComponent<Transform>());
}

void DeckBuildingState::moveToDrawer(Card* card)
{
	//TuVieja("HOSTIA TIO QUE NO LO HE ENCHUFAO - to cajon");

	// ---- al mover una carta al cajon:
	// se elimina de la pizarra
	pizarra_->removeCard(card->getID());

	// se aniade al cajon
	drawer_->addCard(card->getID(), card->getEntity());
}

ecs::entity_t DeckBuildingState::createCard(int id, Vector2D pos)
{
	// Hace LA carta segun su id, en la pos que se pida
	auto card = sdlutils().cards().at(std::to_string(id));
	ecs::entity_t ent = factory->createFakeCard(id, pos, card.cost(), card.value(), card.sprite(), card.unblockable(),
	                                            card.effects());
	return ent;
}
void DeckBuildingState::setTutorial()
{
	if (isTutorial) {

		// entidad tutorial para gestionar cositas
		tutorial = Instantiate();

		tutorial->addComponent<TutorialManager>();
		auto manager = tutorial->addComponent<TutorialDeckBuilderManager>(base, tutorial);
		GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::TUTORIAL_MANAGER, tutorial);

		prepareTutorial();

		tutorial->getComponent<TutorialManager>()->startTutorial();
		tutorial->getComponent<TutorialManager>()->setCurrentTutorial(Tutorials::DECKBUILDER);
		tutorial->getComponent<TutorialManager>()->setCurrentTutorialState(Tutorials::Deckbuilder::DECKBUILDER_NONE);
		tutorial->getComponent<TutorialManager>()->setNextTutorialState(Tutorials::Deckbuilder::DECKBUILDING_INIT);


		int a = tutorial->getComponent<TutorialManager>()->getTutorialState();

		//tutorial->getComponent<TutorialBoardManager>()->setObjs(objs);

	}
}
void DeckBuildingState::prepareTutorial()
{
	// base
	base = Instantiate();
	base->addComponent<Transform>();
	//base->getComponent<Transform>()->addParent(nullptr);
	//base->getComponent<Transform>()->getRelativeScale().set(0.25, 0.25);
	Vector2D pos{ 200, 200 };
	base->getComponent<Transform>()->setGlobalPos(pos);
	base->setLayer(2);

}
void DeckBuildingState::startTutorial(bool a)
{
	isTutorial = a;
}
#pragma endregion

void DeckBuildingState::resetFade()
{
	tweenFade =
		tweeny::from(0)
		.to(255)
		.during(30)
		.to(255)
		.during(60)
		.to(0)
		.during(30)
		.via(tweeny::easing::linear);
}
#pragma endregion

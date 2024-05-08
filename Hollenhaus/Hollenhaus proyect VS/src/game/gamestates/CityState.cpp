#include <../pchs/pch.h>

#include "CityState.h"
#include "../components/basics/TextComponent.h"
#include "../components/MoveOnClick.h"
#include "../components/NPC.h"
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/TypeWriter.h"
#include "../components/NextText.h"
#include "../factories/Factory.h"
#include "../factories/NPCFactory_V0.h"
#include "pauseMenuState.h"
#include "game/components/Clickable.h"
#include "game/components/ImageWithFrames.h"

CityState::CityState()
{
	TuVieja("Loading CityState");
}

CityState::~CityState()
{
}

void CityState::update()
{
	GameState::update();

	/// XD
	fantasmiko->getComponent<SpriteRenderer>()->setFlipX(fondo->getComponent<MoveOnClick>()->getDir());

	/// TWEENSI DEL FANTASMIKO
	fantastween.loop();
	fantastween.step(1);
	auto fanTrans = fantasmiko->getComponent<Transform>();
	if (fantastween.peek() > 0) // una mierda de manera de 1. saber que devuelve un int valido 2. que no se salga
	{
		Vector2D step(
			fanTrans->getGlobalPos().getX(),
			fantastween.peek()
		);
		fanTrans->setGlobalPos(step);
	}
}

void CityState::render() const
{
	GameState::render();
}

void CityState::refresh()
{
	GameState::refresh();
}

void CityState::onEnter()
{
	std::cout << "\nENTER CITY.\n";

	// llamada al input
	ih().insertFunction(ih().PAUSEKEY_DOWN, [this] { onPause(); });

	factory = new Factory();
	factory->SetFactories(
		static_cast<NPCFactory*>(new NPCFactory_V0()));


	/// ---- FONDO CIUDAD ----
	auto scaleFondo = Vector2D(0.495f, 0.495f);
	fondo = Instantiate(Vector2D(0, 2));
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("edificios");
	fondo->addComponent<MoveOnClick>(3.0f);
	fondo->addComponent<BoxCollider>();
	fondo->getComponent<Transform>()->setGlobalScale(scaleFondo);
	Vector2D globalPos = getLastPaulPos();
	Vector2D realFondoPos = Vector2D(globalPos.getX(), globalPos.getY() + 2);
	fondo->getComponent<Transform>()->setGlobalPos(realFondoPos);
	fondo->setLayer(0);

	/// FAROLAS
	auto farolascerca = Instantiate(Vector2D(0, 0));
	auto farCerTrans = farolascerca->getComponent<Transform>();
	farCerTrans->addParent(fondo->getComponent<Transform>());
	farolascerca->addComponent<SpriteRenderer>("farolascerca");
	farolascerca->setLayer(4);
	farCerTrans->setGlobalScale(scaleFondo);
	farCerTrans->setGlobalPos(globalPos);

	auto farolaslejos = Instantiate(Vector2D(Vector2D(0, 0)));
	auto farLejTrans = farolaslejos->getComponent<Transform>();
	farLejTrans->addParent(fondo->getComponent<Transform>());
	farolaslejos->addComponent<SpriteRenderer>("farolaslejos");
	farolaslejos->setLayer(2);
	farLejTrans->setGlobalScale(scaleFondo);
	farLejTrans->setGlobalPos(globalPos);

	farLejTrans->setRelativePos(0, -11);

	/// ---- SUELO ----
	// instancia suelo
	ecs::entity_t colliderSuelo = Instantiate();

	// aniade los componentes
	colliderSuelo->addComponent<Transform>();
	colliderSuelo->addComponent<BoxCollider>();

	// tamanio del collider del suelo
	// x: el ancho de la imagen de fondo, y: alto del suelo
	colliderSuelo->getComponent<BoxCollider>()->setSize(
		Vector2D((fondo->getComponent<SpriteRenderer>()->getTexture()->width()), sdlutils().height() * 2));

	// lo emparenta con el fondo
	colliderSuelo->getComponent<Transform>()->addParent(fondo->getComponent<Transform>());

	// posicion del collider del suelo
	Vector2D vectorSueloPos(0, sdlutils().height() / 2);
	colliderSuelo->getComponent<Transform>()->setRelativePos(vectorSueloPos.getX(), vectorSueloPos.getY());

	// registra el collider del suelo
	fondo->getComponent<MoveOnClick>()->RegisterCollider(colliderSuelo->getComponent<BoxCollider>());


	/// FANTASMIKO
	fantasmiko = Instantiate(Vector2D(sdlutils().width() / 2 - 50, sdlutils().height() - 200));
	fantasmiko->addComponent<SpriteRenderer>("fantasma_caminando");
	fantasmiko->addComponent<BoxCollider>();
	fantasmiko->getComponent<Transform>()->setGlobalScale(Vector2D(0.15f, 0.15f));
	fantasmiko->setLayer(2);
	fantasmiko->addComponent<ImageWithFrames>(fantasmiko->getComponent<SpriteRenderer>(), 1, 4);

	auto moc = fondo->getComponent<MoveOnClick>();
	moc->registerFantasmaTrans(fantasmiko);

	//std::cout << moc->getDir() << getLastPaulDir() << std::endl;
	moc->setDir(getLastPaulDir());
	fantasmiko->getComponent<SpriteRenderer>()->setFlipX(moc->getDir());

	// twinsiiiis
	auto fanY = fantasmiko->getComponent<Transform>()->getGlobalPos().getY();
	fantastween =
		tweeny::from(fanY - 5)
		.to(fanY + 5)
		.to(fanY - 5)
		.during(60)
		.via(tweeny::easing::sinusoidalInOut);
	///




	///------NPCs:
	//----Para entrar en la oficina.
	//factory->createNPC("El Xungo del Barrio", "npc", {0.25f, 0.25f}, {-100, 425}, 0, 3, 2, fondo);
	factory->createNPC(0, fondo);
	factory->createNPC(1, fondo);
	factory->createNPC(2, fondo);
	factory->createNPC(3, fondo);
	factory->createNPC(4, fondo);
	///

	// --- Boton para volver al menu principal ---
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(GameStates::MAINMENU); // Lleva al menu (0).
	exit->setLayer(2);
	exit->addComponent<Clickable>("boton_flecha", true);

	// SDLUTILS
	// referencia a sdlutils
	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("citytheme").play(-1);
	sdl.soundEffects().at("citytheme").setChannelVolume(10);
}

void CityState::onExit()
{
	// se desuscribe al evento
	ih().clearFunction(ih().PAUSEKEY_DOWN, [this] { onPause(); });

	std::cout << "\nEXIT CITY.\n";

	setLastPaulPos(fondo->getComponent<Transform>()->getGlobalPos());
	setLastPaulDir(fondo->getComponent<MoveOnClick>()->getDir());

	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("citytheme").pauseChannel();
	GameStateMachine::instance()->getMngr()->Free();

	delete factory;
}

void CityState::onPause()
{
	SetLastState(1);
	GameStateMachine::instance()->setState(17);
}

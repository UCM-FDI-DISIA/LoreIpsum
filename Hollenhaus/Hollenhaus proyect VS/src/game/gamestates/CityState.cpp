#include "pch.h"
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

CityState::CityState()
{
	TuVieja("Loading CityState");
}

void CityState::update()
{
	GameState::update();

	fantasmiko->getComponent<SpriteRenderer>()->setFlipX(fondo->getComponent<MoveOnClick>()->getDir());

	/// TWEENSI DEL FANTASMIKO
	//tweensy.progress() == 1.0 ? tweensy.backward() : tweensy.forward();
	if (tweensy.progress() == 1.0) tweensy.backward();
	if (tweensy.progress() == 0.0) tweensy.forward();
	tweensy.step(1);
	auto fanTrans = fantasmiko->getComponent<Transform>();
	if (tweensy.peek() > 0) // una mierda de manera de 1. saber que devuelve un int valido 2. que no se salga
	{
		Vector2D step(
			fanTrans->getGlobalPos().getX(),
			tweensy.peek()
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

	factory = new Factory();
	factory->SetFactories(
		static_cast<NPCFactory*>(new NPCFactory_V0())
	);


	//------Texto de la ciudad:
	ecs::entity_t cityText = Instantiate(Vector2D(500, 30));
	cityText->addComponent<TextComponent>("CIUDAD", "8bit_size_40", SDL_Color({255, 255, 255, 255}), 350,
	                                      Text::CenterCenter, Text::Center);
	cityText->setLayer(1);

	// ---- FONDO CIUDAD ----
	fondo = Instantiate();
	//fond = fondo;
	// le aniade los componentes
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("ciudadcompleta");
	fondo->addComponent<MoveOnClick>(2);

	//fondo->getComponent<SpriteRenderer>()->setMultiplyColor(0, 0, 0, 255);
	fondo->addComponent<BoxCollider>();
	//tamanyo de ciudadcompleta.png: 5754 x 1212
	fondo->getComponent<Transform>()->setGlobalScale(0.495f, 0.495f);
	//fondo->getComponent<Transform>()->getGlobalScale().set(0.495f, 0.495f); //escalado para ciudadcompleta.png (porfi no toquetear)!!! 

	//Vector2D globalPos(-1200.0f, 0); //Posici�n inicial de la ciudad para que se vea por el centro.
	Vector2D globalPos = getLastPaulPos();
	fondo->getComponent<Transform>()->setGlobalPos(globalPos);

	// lo pone en la capa correcta
	fondo->setLayer(0);

	// ---- SUELO ----
	// instancia suelo
	ecs::entity_t colliderSuelo = Instantiate();

	// aniade los componentes
	colliderSuelo->addComponent<Transform>();
	colliderSuelo->addComponent<BoxCollider>();

	// tamanio del collider del suelo
	// x: el ancho de la imagen de fondo, y: alto del suelo
	colliderSuelo->getComponent<BoxCollider>()->setSize(
		Vector2D((fondo->getComponent<SpriteRenderer>()->getTexture()->width()), 120));

	// lo emparenta con el fondo
	colliderSuelo->getComponent<Transform>()->addParent(fondo->getComponent<Transform>());

	// posicion del collider del suelo
	Vector2D vectorSueloPos(0, 520);
	colliderSuelo->getComponent<Transform>()->getRelativePos().set(vectorSueloPos);

	// registra el collider del suelo
	fondo->getComponent<MoveOnClick>()->RegisterCollider(colliderSuelo->getComponent<BoxCollider>());

	// ---- PLAYER ----
	fantasmiko = Instantiate(Vector2D(sdlutils().width() / 2 - 50, sdlutils().height() - 200));
	fantasmiko->addComponent<SpriteRenderer>("fantasma");
	fantasmiko->addComponent<BoxCollider>();
	fantasmiko->getComponent<Transform>()->setGlobalScale(Vector2D(0.15f, 0.15f));
	fantasmiko->getComponent<SpriteRenderer>()->setFlipX(true);
	fantasmiko->setLayer(2);
	// twinsiiiis
	auto fanX = fantasmiko->getComponent<Transform>()->getGlobalPos().getY();
	tweensy =
		tweeny::from(fanX - 5)
		.to(fanX + 5)
		.to(fanX - 5)
		.during(60)
		.via(tweeny::easing::sinusoidalInOut);


	//------NPCs:
	//----Para entrar en la oficina.
	//factory->createNPC("El Xungo del Barrio", "npc", {0.25f, 0.25f}, {-100, 425}, 0, 3, 2, fondo);
	factory->createNPC(0, fondo);
	factory->createNPC(1, fondo);
	factory->createNPC(2, fondo);
	factory->createNPC(3, fondo);


	//----Para entrar en la tienda.
	//factory->createNPC("el que te vende la droga idk", "hombre", { 1.0f, 1.0f }, { 800, 425 }, 1, 3, 2, fondo);

	//----Para empezar la batalla.
	//factory->createNPC("Cailtyn", "npc", {0.25f, 0.25f}, {400, 425}, 1, 6, 2, fondo);

	////----Para hablar
	//ecs::entity_t npc4 = Instantiate();
	//npc4->addComponent<Transform>();
	//npc4->addComponent<SpriteRenderer>("NPCNPC");
	//npc4->addComponent<BoxCollider>();
	//npc4->getComponent<Transform>()->addParent(fondo->getComponent<Transform>());
	//npc4->getComponent<Transform>()->getRelativeScale().set(0.25f, 0.25f);
	//Vector2D npc4Pos(600, 425);
	//npc4->getComponent<Transform>()->setGlobalPos(npc4Pos);
	//npc4->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	//npc4->addComponent<NPC>(3, 1, "El Xungo del Barrio");
	//npc4->setLayer(2);

	// --- Boton para volver al menu principal ---
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(0); // Lleva al menu (0).
	exit->setLayer(2);

	// SDLUTILS
	// referencia a sdlutils
	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("citytheme").play(-1);
	sdl.soundEffects().at("citytheme").setChannelVolume(10);
}

void CityState::onExit()
{
	std::cout << "\nEXIT CITY.\n";

	auto& sdl = *SDLUtils::instance();
	setLastPaulPos(fondo->getComponent<Transform>()->getGlobalPos());
	sdl.soundEffects().at("citytheme").pauseChannel();
	GameStateMachine::instance()->getMngr()->Free();
}

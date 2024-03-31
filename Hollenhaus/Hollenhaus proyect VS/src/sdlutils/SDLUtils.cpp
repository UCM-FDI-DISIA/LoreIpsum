// This file is part of the course TPV2@UCM - Samir Genaim
#include "../../pchs/pch_SDL.h"

#include "SDLUtils.h"

#include <cassert>
#include <memory>

#include "../json/JSON.h"

SDLUtils::SDLUtils() :
		SDLUtils("SDL Demo", 600, 400) {
}

SDLUtils::SDLUtils(std::string windowTitle, int width, int height) :
		windowTitle_(windowTitle), //
		width_(width), //
		height_(height), //
		fontsAccessWrapper_(fonts_, "Fonts Table"), //
		imagesAccessWrapper_(images_, "Images Table"), //
		msgsAccessWrapper_(msgs_, "Messages Table"), //
		soundsAccessWrapper_(sounds_, "Sounds Table"), //
		musicsAccessWrapper_(musics_, "Musics Table"), //
		cardAccessWrapper_(cards_, "Cards Table"), //
		dialogueAccessWrapper_(dialogues_, "Dialogues Table"), //
		npcsAccessWrapper_(npcs_, "NPCs Table") //
{
	initWindow();
	initSDLExtensions();
}

SDLUtils::SDLUtils(std::string windowTitle, int width, int height,
		std::string filename, std::string filenameCards, std::string filemaneDialogues, std::string filenameNPCs) :
		SDLUtils(windowTitle, width, height) {
	loadResources(filename,filenameCards,filemaneDialogues, filenameNPCs);
}

SDLUtils::~SDLUtils() {
	closeSDLExtensions();
	closeWindow();
}

void SDLUtils::initWindow() {

#ifdef _DEBUG
	std::cout << "Initializing SDL" << std::endl;
#endif

	// Initialize SDL
	int sdlInit_ret = SDL_Init(SDL_INIT_EVERYTHING);
	assert(sdlInit_ret == 0);

#ifdef _DEBUG
	std::cout << "Creating SDL window" << std::endl;
#endif

	// Create window
	window_ = SDL_CreateWindow(windowTitle_.c_str(),
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_SHOWN);
	assert(window_ != nullptr);

#ifdef _DEBUG
	std::cout << "Creating SDL renderer" << std::endl;
#endif
	// Create the renderer
	renderer_ = SDL_CreateRenderer(window_, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(renderer_ != nullptr);

#if !(_DEBUG)
	toggleFullScreen();
#endif

	// hide cursor by default
	//hideCursor();

}

void SDLUtils::closeWindow() {

	// destroy renderer and window
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	SDL_Quit(); // quit SDL
}

void SDLUtils::initSDLExtensions() {

#ifdef _DEBUG
	std::cout << "Initializing SDL_ttf" << std::endl;
#endif
	// initialize SDL_ttf
	int ttfInit_r = TTF_Init();
	assert(ttfInit_r == 0);

#ifdef _DEBUG
	std::cout << "Initializing SDL_img" << std::endl;
#endif
	// initialize SDL_image
	int imgInit_ret = IMG_Init(
			IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
	assert(imgInit_ret != 0);

#ifdef _DEBUG
	std::cout << "Initializing SDL_Mixer" << std::endl;
#endif
	// initialize SDL_Mixer
	int mixOpenAudio = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	assert(mixOpenAudio == 0);
	int mixInit_ret = Mix_Init(
			MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	assert(mixInit_ret != 0);
	SoundEffect::setNumberofChannels(8); // we start with 8 channels

}

void SDLUtils::loadResources(std::string filenameResources,
	std::string filenameCards, std::string filenameDialogues, 
	std::string filenameNPCs) {
	// TODO check the correctness of values and issue a corresponding
	// exception. Now we just do some simple checks, and assume input
	// is correct.

	// Load JSON configuration file. We use a unique pointer since we
	// can exit the method in different ways, this way we guarantee that
	// it is always deleted

	if (filenameResources == "") {
		std::cout << "No hay ruta de recursos, por lo que no se cargan" << '\n';
		return;
	}

	std::unique_ptr<JSONValue> jValueRootResources(JSON::ParseFromFile(filenameResources));
	std::unique_ptr<JSONValue> jValueRootCards(JSON::ParseFromFile(filenameCards));
	std::unique_ptr<JSONValue> jValueRootDialogues(JSON::ParseFromFile(filenameDialogues));
	std::unique_ptr<JSONValue> jValueRootNPCs(JSON::ParseFromFile(filenameNPCs));

	// check it was loaded correctly
	// the root must be a JSON object
	if (jValueRootResources == nullptr || !jValueRootResources->IsObject()) {
		throw "Something went wrong while load/parsing '" + filenameResources + "'";
	}
	// check it was loaded correctly
	// the root must be a JSON object
	if (jValueRootCards == nullptr || !jValueRootCards->IsObject()) {
		throw "Something went wrong while load/parsing '" + filenameCards + "'";
	}
	// check it was loaded correctly
	// the root must be a JSON object
	if (jValueRootDialogues == nullptr || !jValueRootDialogues->IsObject()) {
		throw "Something went wrong while load/parsing '" + filenameDialogues + "'";
	}
	// check it was loaded correctly
	// the root must be a JSON object
	if (jValueRootNPCs == nullptr || !jValueRootNPCs->IsObject()) {
		throw "Something went wrong while load/parsing '" + filenameNPCs + "'";
	}

	// we know the root is JSONObject
	JSONObject rootResources = jValueRootResources->AsObject();
	JSONObject rootCards = jValueRootCards->AsObject();
	JSONObject rootDialogues = jValueRootDialogues->AsObject();
	JSONObject rootNPCs = jValueRootNPCs->AsObject();



	// TODO improve syntax error checks below, now we do not check
	//      validity of keys with values as sting or integer

	loadFonts(rootResources, filenameResources);
	loadImages(rootResources, filenameResources);
	loadMusics(rootResources, filenameResources);
	loadSounds(rootResources, filenameResources);
	loadMessages(rootResources, filenameResources);
	loadCards(rootCards, filenameResources);
	loadDialogues(rootDialogues, filenameDialogues);
	loadNPCs(rootNPCs, filenameNPCs);
}

void SDLUtils::loadFonts(JSONObject rootResources, std::string filenameResources)
{
	// load fonts
	const JSONValue *jValue = jValue = rootResources["fonts"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			fonts_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
					uint8_t size =
							static_cast<uint8_t>(vObj["size"]->AsNumber());
#ifdef _DEBUG
					std::cout << "Loading font with id: " << key << std::endl;
#endif
					fonts_.emplace(key, Font(file, size));
				} else {
					throw "'fonts' array in '" + filenameResources
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'fonts' is not an array in '" + filenameResources + "'";
		}
	}
}

void SDLUtils::loadImages(JSONObject rootResources, std::string filenameResources)
{
	// load images
	const auto jValue = rootResources["images"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			images_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
#ifdef _DEBUG
					std::cout << "Loading image with id: " << key << std::endl;
#endif
					images_.emplace(key, Texture(renderer(), file));
				} else {
					throw "'images' array in '" + filenameResources
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'images' is not an array in '" + filenameResources + "'";
		}
	}
}

void SDLUtils::loadMusics(JSONObject rootResources, std::string filenameResources)
{
	// load musics
	const auto jValue = rootResources["musics"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			musics_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
#ifdef _DEBUG
					std::cout << "Loading music with id: " << key << std::endl;
#endif
					musics_.emplace(key, Music(file));
				} else {
					throw "'musics' array in '" + filenameResources
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'musics' is not an array";
		}
	}
}

void SDLUtils::loadSounds(JSONObject rootResources, std::string filenameResources)
{
	// load sounds
	const auto jValue = rootResources["sounds"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			sounds_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
#ifdef _DEBUG
					std::cout << "Loading sound effect with id: " << key
							<< std::endl;
#endif
					sounds_.emplace(key, SoundEffect(file));
				} else {
					throw "'sounds' array in '" + filenameResources
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'sounds' is not an array";
		}
	}
}


void SDLUtils::loadMessages(JSONObject rootResources, std::string filenameResources)
{
	// load messages
	const auto jValue = rootResources["messages"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			msgs_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto& v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string txt = vObj["text"]->AsString();
					auto& font = fonts_.at(vObj["font"]->AsString());
#ifdef _DEBUG
					std::cout << "Loading message with id: " << key
						<< std::endl;
#endif
					if (vObj["bg"] == nullptr)
						msgs_.emplace(key,
							Texture(renderer(), txt, font,
								build_sdlcolor(
									vObj["color"]->AsString())));
					else
						msgs_.emplace(key,
							Texture(renderer(), txt, font,
								build_sdlcolor(
									vObj["color"]->AsString()),
								build_sdlcolor(
									vObj["bg"]->AsString())));
				}
				else {
					throw "'messages' array in '" + filenameResources
						+ "' includes and invalid value";
				}
			}
		}
		else {
			throw "'messages' is not an array in '" + filenameResources + "'";
		}
	}
}


void SDLUtils::loadCards(JSONObject rootCards, std::string filenameCards)
{
	/// CARD PARSING
	///	Samir (feat. Cynthia)
	const auto jValue = rootCards["cards"]; // key con todas las cartas
	if (jValue != nullptr) { // si existe tal key
		if (jValue->IsArray()) { // si tiene cartas dentro
			cards_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) { // por cada carta
				if (v->IsObject()) { // si la carta actual es objeto
					// card as JSON object
					JSONObject cardObj = v->AsObject();

					/// >>> Lectura inicial de parametros basicos <<<
					std::string key		= cardObj["id"]->AsString(); // id
					int cost			= cardObj["cost"]->AsNumber(); // coste
					int value			= cardObj["value"]->AsNumber(); // valor 
					std::string sprite	= cardObj["sprite"]->AsString(); // sprite
					bool unblockable	= cardObj["unblockable"]->AsBool(); // unblockable


					/// >>> Lectura de efectos <<<
					/// Por cada carta, hay un array de efectos
					std::vector<JsonData::CardEffect> effects; // declaracion inicial de vector vacio de efectos
					auto effArr = cardObj["effects"]->AsArray(); // effects as JSON array derivate of card object
					for (auto& e : effArr ) // por cada efecto
					{ // each effect as JSON object
						auto effObj = e->AsObject();

						/// El UNICO requerimiento que tiene un efecto es su tipo de efecto
						///	Si ese tipo de efecto necesita otros valores que no tiene, se usan unos
						///	por defecto
						
						// casting de int a enum de efecto
						Effects::Type type = static_cast<Effects::Type>(effObj["type"]->AsNumber());

						/// Hay efectos que pueden NO tener valor numerico
						int effValue = 0;
						if (effObj["value"] != nullptr)
							effValue = effObj["value"]->AsNumber();

						/// Por cada efecto, puede haber un array de direcciones
						///	(en caso de que no haya direcciones, el vector es vacio y punto pelota)
						std::vector<Effects::Direction> directions;
						loadDirections(effObj, directions);

						effects.emplace_back(type, effValue, directions);
					}
#ifdef _DEBUG
					std::cout << "Loading cards with id: " << key << std::endl;
#endif
					cards_.emplace(key, JsonData::CardData(cost, value, sprite, unblockable, effects)); // finalmente se anyaden al mapa

				} else {
					throw "'cards' array in '" + filenameCards
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'cards' is not an array";
		}
	}
}



void SDLUtils::loadDialogues(JSONObject rootDialogues, std::string filenameDialogues)
{
	// DIALOGUES PARSING
	// Samir, Cynthia (feat. Luis & Ines)
	const auto jValue = rootDialogues["owner"];	// key con todos los owners
	if (jValue != nullptr) {	// si existe la key "owner"
		if (jValue->IsArray()) {	// si existen owners
			for (auto& v : jValue->AsArray()) {	// por cada owner
				if (v->IsObject()) {	// si el owner es un objeto
					JSONObject ownerObj = v->AsObject();	// guardamos el owner como JSONObject
					std::string NPCName = ownerObj["NPCName"]->AsString();	// Obtenemos la key "NPCName" del JSONObject creado por cada owner
					int NPCID = ownerObj["NPCID"]->AsNumber();

					std::vector<JsonData::ConvoData> convos;		// Declaramos el vector para guardar las convos del owner
																	// Las convos aun no se pueden guardar porque dentro hay varios datos que quedan por parsear
					
					JSONArray convosArray = ownerObj["convo"]->AsArray();	// Array de convos
					for (auto& c : convosArray) {	// Por cada convo
						if (c->IsObject()) {
							JSONObject convoObj = c->AsObject();	// Guardamos la convo como objeto
							int convoID = convoObj["convoID"]->AsNumber();	// Obteneos la key "convoID" del JSONObject creado por cada convo
							bool auto_ = convoObj["autoConvo"]->AsBool();

							std::vector<JsonData::NodeData> nodes;	// Declaramos el vector para guardar los nodos de la convo
																	// Los nodos aun no se pueden guardar porque dentro hay varios datos que quedan por parsear
					
							JSONArray nodesArray = convoObj["nodes"]->AsArray();	// Array de nodes
							for (auto& n : nodesArray) {		// Por cada node
								if (n->IsObject()) {
									JSONObject nodeObj = n->AsObject();
									int nodeID = nodeObj["nodeID"]->AsNumber();
									std::string text = nodeObj["text"]->AsString();

									DialogueEvents::Events eventStart = static_cast<DialogueEvents::Events>(nodeObj["eventStart"]->AsNumber());
									DialogueEvents::Events eventFinish = static_cast<DialogueEvents::Events>(nodeObj["eventFinish"]->AsNumber());

									//vector de efectos
									std::vector<JsonData::DialogueEventS> eventsS;
									std::vector<JsonData::DialogueEventS> eventsF;

									JSONArray eventsA = nodeObj["events"]->AsArray();	// Array de eventos iniciales
									for (auto& ea : eventsA) {
										if (ea->IsObject()) {
											JSONObject eventObj = ea->AsObject();

											// recoge los datos
											int timing = eventObj["timing"]->AsNumber();
											int type = eventObj["type"]->AsNumber();
											int scene = eventObj["scene"]->AsNumber();

											switch (timing) {
											case 0:
												eventsS.emplace_back(timing, type, scene);
												break;
											case 1:
												eventsF.emplace_back(timing, type, scene);
												break;
											default:
												break;
											}
										}
									}
									nodes.emplace_back(nodeID, text, eventStart, eventFinish, eventsS, eventsF);
								}
							}

							convos.emplace_back(convoID, auto_, nodes);
						}
					}
#ifdef _DEBUG
					std::cout << "Loading dialogues of owner: " << NPCName << std::endl;
#endif
					dialogues_.emplace(NPCName, JsonData::DialogueData(NPCName, NPCID, convos));
				}
				else {
					throw "'dialogues' array in '" + filenameDialogues
						+ "' includes and invalid value";
				}
			}
		}
		else {
			throw "'dialogues' is not an array";
		}
	}
}

void SDLUtils::loadNPCs(JSONObject rootNPCSs, std::string filenameNPCs)
{
	/// CARD PARSING
	///	Samir (feat. Ines)
	const auto jValue = rootNPCSs["npcs"]; // key con todos los npcs
	if (jValue != nullptr) { // si existe tal key
		if (jValue->IsArray()) { // si tiene npcs dentro
			npcs_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto& v : jValue->AsArray()) { // por cada npc
				if (v->IsObject()) { // si el npc actual es objeto
					// npc as JSON object
					JSONObject npcObj = v->AsObject();
					
					/// >>> Lectura inicial de parametros basicos <<<
					std::string id = npcObj["npcID"]->AsString();
					std::string name = npcObj["name"]->AsString(); // id
					std::string sprite = npcObj["sprite"]->AsString(); // sprite
					float sX = npcObj["scaleX"]->AsNumber(); // scale X
					float sY = npcObj["scaleY"]->AsNumber(); // scale Y
					float pX = npcObj["posX"]->AsNumber(); // position X
					float pY = npcObj["posY"]->AsNumber(); // position Y
					int type = npcObj["type"]->AsNumber(); // type
					int scene = npcObj["scene"]->AsNumber(); // scene
					int layer = npcObj["layer"]->AsNumber(); // layer

					JsonData::NPCData info(std::stoi(id), name, sprite, sX, sY, pX, pY, type, scene, layer);
					JsonData::NPCData rinfo = static_cast<JsonData::NPCData>(info);

#ifdef _DEBUG
					std::cout << "Loading NPC with id: " << id << std::endl;
#endif
					npcs_.emplace(id, rinfo); // finalmente se anyaden al mapa
				}
				else {
					throw "'npcs' array in '" + filenameNPCs
						+ "' includes and invalid value";
				}
			}
		}
		else {
			throw "'npcs' is not an array";
		}
	}

}

std::vector<Effects::Direction>& SDLUtils::loadDirections(JSONObject& jo, std::vector<Effects::Direction>& directions)
{
	if (jo["directions"] == nullptr) return directions; // si no tiene direcciones, vuelve

	const auto dirArr = jo["directions"]->AsArray(); // si las tiene

	for (const auto& d : dirArr) // por cada direccion, 
	{
		auto dir = d->AsString();

		for (char &c : dir) 
			c = std::tolower(c);

		// soy tonti y no se pueden usar switchs con strings </3
		// esto deberia ir en otro lado siiiii no me mires estoy probando
		if		(dir == "up"	|| dir == "arriba")
			directions.push_back(Effects::Up);
		else if (dir == "right" || dir == "derecha")
			directions.push_back(Effects::Right);
		else if (dir == "down"	|| dir == "abajo")
			directions.push_back(Effects::Down);
		else if (dir == "left"	|| dir == "izquierda")
			directions.push_back(Effects::Left);
	}

	return directions;
}

void SDLUtils::closeSDLExtensions() {

	musics_.clear();
	sounds_.clear();
	msgs_.clear();
	images_.clear();
	fonts_.clear();
	cards_.clear();

	Mix_Quit(); // quit SDL_mixer
	IMG_Quit(); // quit SDL_image
	TTF_Quit(); // quit SDL_ttf
}


// This file is part of the course TPV2@UCM - Samir Genaim

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
		cardAccessWrapper(cards_, "Cards Table") //
{
	initWindow();
	initSDLExtensions();
}

SDLUtils::SDLUtils(std::string windowTitle, int width, int height,
		std::string filename) :
		SDLUtils(windowTitle, width, height) {
	loadReasources(filename);
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

void SDLUtils::loadReasources(std::string filename) {
	// TODO check the correctness of values and issue a corresponding
	// exception. Now we just do some simple checks, and assume input
	// is correct.

	// Load JSON configuration file. We use a unique pointer since we
	// can exit the method in different ways, this way we guarantee that
	// it is always deleted

	if (filename == "") {
		std::cout << "No hay ruta de recursos, por lo que no se cargan" << '\n';
		return;
	}

	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

	// check it was loaded correctly
	// the root must be a JSON object
	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + filename + "'";
	}

	// we know the root is JSONObject
	JSONObject root = jValueRoot->AsObject();
	JSONValue *jValue = nullptr;

	// TODO improve syntax error checks below, now we do not check
	//      validity of keys with values as sting or integer

	// load fonts
	jValue = root["fonts"];
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
					throw "'fonts' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'fonts' is not an array in '" + filename + "'";
		}
	}

	// load images
	jValue = root["images"];
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
					throw "'images' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'images' is not an array in '" + filename + "'";
		}
	}

	// load messages
	jValue = root["messages"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			msgs_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string txt = vObj["text"]->AsString();
					auto &font = fonts_.at(vObj["font"]->AsString());
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
				} else {
					throw "'messages' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'messages' is not an array in '" + filename + "'";
		}
	}

	// load sounds
	jValue = root["sounds"];
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
					throw "'sounds' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'sounds' is not an array";
		}
	}

	// load musics
	jValue = root["musics"];
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
					throw "'musics' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'musics' is not an array";
		}
	}




	/// CARD PARSING
	///	Samir (feat. Cynthia)
	jValue = root["cards"]; // key con todas las cartas
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
					std::vector<CardEffect> effects; // declaracion inicial de vector vacio de efectos
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
						std::vector<CellData::Direction> directions;
						loadDirections(effObj, directions);

						effects.emplace_back(type, effValue, directions);
					}
#ifdef _DEBUG
					std::cout << "Loading cards with id: " << key << std::endl;
#endif
					cards_.emplace(key, CardData(cost, value, sprite, unblockable, effects)); // finalmente se anyaden al mapa

				} else {
					throw "'cards' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'cards' is not an array";
		}
	}
}

std::vector<CellData::Direction>& SDLUtils::loadDirections(JSONObject& jo, std::vector<CellData::Direction>& directions)
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
			directions.push_back(CellData::Up);
		else if (dir == "right" || dir == "derecha")
			directions.push_back(CellData::Right);
		else if (dir == "down"	|| dir == "abajo")
			directions.push_back(CellData::Down);
		else if (dir == "left"	|| dir == "izquierda")
			directions.push_back(CellData::Left);
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


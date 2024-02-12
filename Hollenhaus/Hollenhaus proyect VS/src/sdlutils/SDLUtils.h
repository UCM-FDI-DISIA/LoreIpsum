// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include <string>
#include <unordered_map>

#include "../utils/Singleton.h"
#include "RandomNumberGenerator.h"
#include "Font.h"
#include "Music.h"
#include "SoundEffect.h"
#include "Texture.h"
#include "VirtualTimer.h"

class SDLUtils: public Singleton<SDLUtils> {

	friend Singleton<SDLUtils> ; // needed to give access to private constructors

public:

	// we abstract away the actual data structure we use for
	// tables. All we assume is that is has the following
	// methods
	//
	//   emplace(key,value)
	//   at(key)
	//   reserve(unsigned int)
	//   clear()
	//
	template<typename T>
	using sdl_resource_table = std::unordered_map<std::string,T>;

	// just a wrapper for accessing a map, to protect the table and
	// to throw a meaningful exception when the key is not found
	// in the original map
	//
	template<typename T>
	class map_access_wrapper {
		sdl_resource_table<T> &map_;
		std::string desc_;
	public:
		map_access_wrapper(sdl_resource_table<T> &map, std::string desc) :
				map_(map), desc_(desc) {
		}

		inline T& at(const std::string &key) {
			try {
				return map_.at(key);
			} catch (std::out_of_range &e) {
				throw "Key '" + key + "' does not exists in '" + desc_ + "'";
			} catch (std::exception &e) {
				throw "Error when accessing key '" + key + "' of '" + //
						desc_ + "'. Original error was: " + e.what();
			} catch (...) {
				throw "Unknown error when accessing key '" + key + "' of '" + //
						desc_ + "'";
			}
		}

		inline T& operator[](const std::string &key) {
			return at(key);
		}
	};

	virtual ~SDLUtils();

	// cannot copy/move
	SDLUtils(SDLUtils&) = delete;
	SDLUtils(SDLUtils&&) = delete;
	SDLUtils& operator=(SDLUtils&) = delete;
	SDLUtils& operator=(SDLUtils&&) = delete;

	// access to the underlying SDL_Window -- in principle not needed
	inline SDL_Window* window() {
		return window_;
	}

	// access to the underlying SDL_Renderer -- needed when creating textures
	// other than those initialised in this class
	inline SDL_Renderer* renderer() {
		return renderer_;
	}

	// clear the renderer with a given SDL_Color
	inline void clearRenderer(SDL_Color bg = build_sdlcolor(0xAAAAAFF)) {
		SDL_SetRenderDrawColor(renderer_, COLOREXP(bg));
		SDL_RenderClear(renderer_);
	}

// present the current content of the renderer
	inline void presentRenderer() {
		SDL_RenderPresent(renderer_);
	}

// the window's width
	inline int width() {
		return width_;
	}

// the window's height
	inline int height() {
		return height_;
	}

// toggle to full-screen/window mode
	inline void toggleFullScreen() {
		auto flags = SDL_GetWindowFlags(window_);
		if (flags & SDL_WINDOW_FULLSCREEN) {
			SDL_SetWindowFullscreen(window_, 0);
		} else {
			SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
		}
	}

// show the cursor when mouse is over the window
	inline void showCursor() {
		SDL_ShowCursor(1);
	}

// hide the cursor when mouse is over the window
	inline void hideCursor() {
		SDL_ShowCursor(0);
	}

// All resource maps can be modified from outside, this way you can store
// your own dynamically. Be careful when modifying them!

// fonts map
	inline auto& fonts() {
		return fontsAccessWrapper_;
	}

// images map
	inline auto& images() {
		return imagesAccessWrapper_;
	}

// messages map
	inline auto& msgs() {
		return msgsAccessWrapper_;
	}

// sound effects map
	inline auto& soundEffects() {
		return soundsAccessWrapper_;
	}

// musics maps
	inline auto& musics() {
		return musicsAccessWrapper_;
	}

// Access to the random number generator. It is important to always
// use this generator, this way you can regenerate the same sequence
// if you start from the same seed
	inline RandomNumberGenerator& rand() {
		return random_;
	}

// Access to the virtual timer, it is useful when you allow to 'pause'
// your game, also for synchronising clocks of players (when using sdlnet)
	inline VirtualTimer& virtualTimer() {
		return timer_;
	}

// Access to real time
	inline Uint32 currRealTime() const {
		return SDL_GetTicks();
	}

private:
	SDLUtils();
	SDLUtils(std::string windowTitle, int width, int height);
	SDLUtils(std::string windowTitle, int width, int height,
			std::string filename);

	void initWindow();
	void closeWindow();
	void initSDLExtensions(); // initialize resources (fonts, textures, audio, etc.)
	void closeSDLExtensions(); // free resources the
	void loadReasources(std::string filename); // load resources from the json file

	std::string windowTitle_; // window title
	int width_; // window width
	int height_; // window height

	SDL_Window *window_; // the window
	SDL_Renderer *renderer_; // the renderer

	sdl_resource_table<Font> fonts_; // fonts map (string -> font)
	sdl_resource_table<Texture> images_; // textures map (string -> texture)
	sdl_resource_table<Texture> msgs_; // textures map (string -> texture)
	sdl_resource_table<SoundEffect> sounds_; // sounds map (string -> sound)
	sdl_resource_table<Music> musics_; // musics map (string -> music)

	map_access_wrapper<Font> fontsAccessWrapper_;
	map_access_wrapper<Texture> imagesAccessWrapper_;
	map_access_wrapper<Texture> msgsAccessWrapper_;
	map_access_wrapper<SoundEffect> soundsAccessWrapper_;
	map_access_wrapper<Music> musicsAccessWrapper_;

	RandomNumberGenerator random_; // (pseudo) random numbers generator
	VirtualTimer timer_; // virtual timer
};

// This macro defines a compact way for using the singleton SDLUtils, instead of
// writing SDLUtils::instance()->method() we write sdlutils().method()
//
inline SDLUtils& sdlutils() {
	return *SDLUtils::instance();
}

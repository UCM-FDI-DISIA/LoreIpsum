// Basado en el codigo para TPV2@UCM - Samir Genaim

#pragma once

#include <iostream>
#include <SDL.h>
#include <array>
#include <map>
#include <functional>

// Instead of a Singleton class, we could make it part of SDLUtils as well
#include "../utils/Singleton.h"



class InputHandler: public Singleton<InputHandler> {
private:
	// utiliza callbacks funcionales de tipo <void(void)>
	using SDLEventCallback = std::function<void(void)>;

	SDLEventCallback funcCallback;

	enum inputState {
		// definir los diferentes eventos de input
	};

	// lista de funciones a llamar cuando sucede un evento
	std::list<SDLEventCallback> inputCallbacks;

	// map <clave: ENUM de eventos (int -> índice del enum), valor: lista de callbacks>
	std::map<inputState, std::list<SDLEventCallback>> inputMap;

	friend Singleton<InputHandler> ;
	
public:
	enum MOUSEBUTTON : uint8_t {
		LEFT = 0, MIDDLE, RIGHT, _LAST_MOUSEBUTTON_VALUE
	};

	virtual ~InputHandler() {
	}

	// clear the state -> pone a false todos los eventos
	inline void clearState() {
		isCloseWindoEvent_ = false;
		isKeyDownEvent_ = false;
		isKeyUpEvent_ = false;

		isMouseButtonUpEvent_ = false;
		isMouseButtonDownEvent_ = false;

		isMouseMotionEvent_ = false;
	}

	// actualiza el estado con un nuvo evento
	inline void update(const SDL_Event &event) {
		switch (event.type) {
			case SDL_KEYDOWN:
				onKeyDown(event);
				break;
			case SDL_KEYUP:
				onKeyUp(event);
				break;
			case SDL_MOUSEMOTION:
				onMouseMotion(event);
				break;
			case SDL_MOUSEBUTTONDOWN:
				onMouseButtonDown(event);
				break;
			case SDL_MOUSEBUTTONUP:
				onMouseButtonUp(event);
				break;
			case SDL_WINDOWEVENT:
				handleWindowEvent(event);
				break;
		default:
			break;
		}
	}

	// refresh
	inline void refresh() {
		SDL_Event event;

		clearState();
		while (SDL_PollEvent(&event))
			update(event);
	}

	// recibe una clave (indice del enum de eventos) y una funcion, inserta esa funcion en el hueco correspondiente a su clave
	void insertFunction(int clave, SDLEventCallback funcCallback) {
		// añade el callback a la lista correspondiente a su clave
		// en ese indice hacer pushback del callback a su lista correspondiente
	}

	// funcion para quitar funciones del map con la clave
	void clearFunction() {

	}

	// devuelve el bool evento activo
#pragma region DEF. EVENTOS

// WINDOW EVENTS
	inline bool closeWindowEvent() {
		return isCloseWindoEvent_;
	}

// KEYBOARD EVENTS
	inline bool keyDownEvent() {
		return isKeyDownEvent_;
	}

	inline bool keyUpEvent() {
		return isKeyUpEvent_;
	}

	inline bool isKeyDown(SDL_Scancode key) {
		return kbState_[key] == 1;
	}

	inline bool isKeyDown(SDL_Keycode key) {
		return isKeyDown(SDL_GetScancodeFromKey(key));
	}

	inline bool isKeyUp(SDL_Scancode key) {
		return kbState_[key] == 0;
	}

	inline bool isKeyUp(SDL_Keycode key) {
		return isKeyUp(SDL_GetScancodeFromKey(key));
	}

// MOUSE EVENTS
	inline bool mouseMotionEvent() {
		return isMouseMotionEvent_;
	}

	inline bool mouseButtonEvent() {
		return isMouseButtonUpEvent_ || isMouseButtonDownEvent_;
	}

	inline bool mouseButtonUpEvent() {
		return isMouseButtonUpEvent_;
	}

	inline bool mouseButtonDownEvent() {
		return isMouseButtonDownEvent_;
	}

	inline const std::pair<Sint32, Sint32>& getMousePos() {
		return mousePos_;
	}

	inline int getMouseButtonState(uint8_t b) {
		assert(b < _LAST_MOUSEBUTTON_VALUE);
		return mbState_[b];
	}

#pragma endregion

private:
	InputHandler() {
		// estado del teclado en ese momento -> qué tecla/s se está pulsando
		// devuelve un puntero a un array de key states -> si un elemento del array es 1 PULSADO / 0 NO PULSADO
		kbState_ = SDL_GetKeyboardState(0); 

		// limpia estado
		clearState();
	}

#pragma region SETTEA EVENTOS A TRUE
	inline void onKeyDown(const SDL_Event&) {
		isKeyDownEvent_ = true;
	}

	inline void onKeyUp(const SDL_Event&) {
		isKeyUpEvent_ = true;
	}

	inline void onMouseMotion(const SDL_Event &event) {
		isMouseMotionEvent_ = true;
		mousePos_.first = event.motion.x;
		mousePos_.second = event.motion.y;
	}

	inline void onMouseButtonDown(const SDL_Event &event) {
		isMouseButtonDownEvent_ = true;
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			mbState_[LEFT] = true;
			break;
		case SDL_BUTTON_MIDDLE:
			mbState_[MIDDLE] = true;
			break;
		case SDL_BUTTON_RIGHT:
			mbState_[RIGHT] = true;
			break;
		default:
			break;
		}
	}

	inline void onMouseButtonUp(const SDL_Event &event) {
		isMouseButtonUpEvent_ = true;
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			mbState_[LEFT] = false;
			break;
		case SDL_BUTTON_MIDDLE:
			mbState_[MIDDLE] = false;
			break;
		case SDL_BUTTON_RIGHT:
			mbState_[RIGHT] = false;
			break;
		default:
			break;
		}
	}

	inline void handleWindowEvent(const SDL_Event &event) {
		switch (event.window.event) {
		case SDL_WINDOWEVENT_CLOSE:
			isCloseWindoEvent_ = true;
			break;
		default:
			break;
		}
	}
#pragma endregion

	// eventos
	bool isCloseWindoEvent_;
	bool isKeyUpEvent_;
	bool isKeyDownEvent_;
	bool isMouseMotionEvent_;
	bool isMouseButtonUpEvent_;
	bool isMouseButtonDownEvent_;

	// posicion del cursor en pantalla
	std::pair<Sint32, Sint32> mousePos_;

	// estados de raton
	std::array<bool, 3> mbState_;

	// puntero a estado de teclado
	const Uint8 *kbState_;
};

// --------
// forma de usar el singleton InputHandler
// InputHandler::instance()->method() / EN VEZ DE ESTO
// ih().method() / ESCRIBIR ESTO
inline InputHandler& ih() {
	return *InputHandler::instance();
}

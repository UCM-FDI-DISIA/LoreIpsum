// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <iostream>
#include <SDL.h>
#include <array>

#include "../utils/Singleton.h"

// Instead of a Singleton class, we could make it part of
// SDLUtils as well.

class InputHandler: public Singleton<InputHandler> {

	friend Singleton<InputHandler> ;

public:
	enum MOUSEBUTTON : uint8_t {
		LEFT = 0, MIDDLE, RIGHT, _LAST_MOUSEBUTTON_VALUE
	};

	virtual ~InputHandler() {
	}

	// clear the state
	inline void clearState() {
		isCloseWindoEvent_ = false;
		isKeyDownEvent_ = false;
		isKeyUpEvent_ = false;

		isMouseButtonUpEvent_ = false;
		isMouseButtonDownEvent_ = false;

		isMouseMotionEvent_ = false;
	}

	// update the state with a new event
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

	// close window event
	inline bool closeWindowEvent() {
		return isCloseWindoEvent_;
	}

	// keyboard
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

	// mouse
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

	// TODO add support for Joystick, see Chapter 4 of
	// the book 'SDL Game Development'

private:
	InputHandler() {
		kbState_ = SDL_GetKeyboardState(0);
		clearState();
	}

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

	bool isCloseWindoEvent_;
	bool isKeyUpEvent_;
	bool isKeyDownEvent_;
	bool isMouseMotionEvent_;
	bool isMouseButtonUpEvent_;
	bool isMouseButtonDownEvent_;
	std::pair<Sint32, Sint32> mousePos_;
	std::array<bool, 3> mbState_;
	const Uint8 *kbState_;
}
;

// This macro defines a compact way for using the singleton InputHandler, instead of
// writing InputHandler::instance()->method() we write ih().method()
//
inline InputHandler& ih() {
	return *InputHandler::instance();
}

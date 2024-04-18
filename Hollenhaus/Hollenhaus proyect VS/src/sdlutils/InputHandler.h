// Basado en el codigo para TPV2@UCM - Samir Genaim

#pragma once

#include <iostream>
#include <SDL.h>
#include <array>
#include <functional>

// Instead of a Singleton class, we could make it part of SDLUtils as well
#include "../utils/Singleton.h"

class InputHandler : public Singleton<InputHandler>
{
private:
	// utiliza callbacks funcionales de tipo <void(void)>
	using SDLEventCallback = std::function<void(void)>;

	// map <clave: ENUM de eventos (int -> índice del enum), valor: lista de callbacks>
	std::unordered_map<int, std::list<SDLEventCallback>> inputMap;

	friend Singleton<InputHandler>;

public:
	enum MOUSEBUTTON : uint8_t
	{
		LEFT = 0,
		MIDDLE,
		RIGHT,
		_LAST_MOUSEBUTTON_VALUE
	};

	/// <summary>
	/// Enum con los eventos que queremos que tengan una lista de callBacks
	/// </summary>
	enum INPUT_EVENTES : uint8_t
	{
		MOUSE_LEFT_CLICK_DOWN,
		MOUSE_LEFT_CLICK_UP,
		KEY_F11_DOWN,
		KEY_F11_UP,
		PAUSEKEY_DOWN,
		PAUSEKEY_UP
	};

	~InputHandler() override
	{
	}

	// clear the state -> pone a false todos los eventos
	void clearState()
	{
		isCloseWindoEvent_ = false;
		isKeyDownEvent_ = false;
		isKeyUpEvent_ = false;

		isMouseButtonUpEvent_ = false;
		isMouseButtonDownEvent_ = false;

		isMouseMotionEvent_ = false;
	}

	// actualiza el estado con un nuvo evento
	void update(const SDL_Event& event)
	{
		//UPDATE BASICO DEL INPUT HANDLER
		switch (event.type)
		{
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

		//UPDATE PARA EL MANEJO DE EVENTOS POR LISTA DE CALLBACKS

		//Obtenemos el indice de nuestro enumerado, segun el evento actual
		//si el evento no está registrado esto devuelve -1s
		int mapIndex = getInputEvent(event);

		//si el evento está registrado
		if (inputMap.find(mapIndex) != inputMap.end())
		{
			// llama a todas las funciones registradas en un evento especifico
			for (SDLEventCallback callback : inputMap.at(mapIndex))
			{
				callback();
			}
		}
	}

	// FUNCION PARA SUSCRIBIRSE A EVENTOS
	// recibe una clave (indice del enum propio de la clase) y una funcion, inserta esa funcion en el hueco correspondiente a su clave
	void insertFunction(int clave, SDLEventCallback funcCallback)
	{
		//buscamos la clave
		auto it = inputMap.find(clave);
		//si la clave no está la insertamos
		if (it == inputMap.end())
		{
			it = inputMap.insert({clave, std::list<SDLEventCallback>()}).first;
		}

		//nos hemos asegurado de que la clave está

		// accede a la lista de callbacks correspondiente a esa clave y añades la funcion a la lista
		it->second.push_back(funcCallback);

		//debug
		//std::cout << "se inserta" << std::endl;
	}

	// funcion para quitar funciones del map con la clave(enum de esta clase)
	void clearFunction(int clave, SDLEventCallback Callback)
	{
		//buscamos la lista de callbacks para ese evento
		auto it = inputMap.find(clave);
		//si no hay ninguna lista,lanzar error y no hacer nada
		if (it == inputMap.end())
		{
			//throw error...
			return;
		}

		//alias, puntero a la lista de callBacks para este evento
		auto& list = it->second;

		//si la lista sí está, recorremos la lista y eliminamos la funcion que nos han pasado
		list.erase(std::remove_if(list.begin(), list.end(),
		                          [&](const SDLEventCallback& cb)
		                          {
			                          return cb.target<void()>() == Callback.target<void()>();
		                          }), list.end());

		//debug
		std::cout << "se quita" << std::endl;
	}

	//devuelve el enumerado correspondiente al evento de SDL
	//si se añade un nuevo valor al enum, hay que actualizar esta funcion para que 
	//detecte el evento concreto que queramos tratar
	int getInputEvent(const SDL_Event& event)
	{
		//EVENTO DE CLICK_IZQ PULSADO
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				return MOUSE_LEFT_CLICK_DOWN;
			}
		}

		//EVENTO DE CLICK_IZQ LEVANTADO
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				return MOUSE_LEFT_CLICK_UP;
			}
		}

		// CUALQUIER KEY
		if (event.type == SDL_KEYDOWN)
		{
			if (event.button.button == SDL_SCANCODE_F11)
			{
				return KEY_F11_DOWN;
			}
			if (event.button.button == SDL_SCANCODE_ESCAPE)
			{
				return PAUSEKEY_DOWN;
			}
		}

		if (event.type == SDL_KEYUP)
		{
			if (event.button.button == SDL_SCANCODE_F11)
			{
				return KEY_F11_UP;
			}
			if (event.button.button == SDL_SCANCODE_ESCAPE)
			{
				return PAUSEKEY_UP;
			}
		}

		//si no es ninguno de los eventos del enumerado devolvemos -1
		return -1;
	}

	// refresh
	void refresh()
	{
		SDL_Event event;

		clearState();
		while (SDL_PollEvent(&event))
			update(event);
	}

#pragma region DEF. EVENTOS

	// devuelve el bool evento activo

	// WINDOW EVENTS
	bool closeWindowEvent()
	{
		return isCloseWindoEvent_;
	}

	// KEYBOARD EVENTS
	bool keyDownEvent()
	{
		return isKeyDownEvent_;
	}

	bool keyUpEvent()
	{
		return isKeyUpEvent_;
	}

	bool isKeyDown(SDL_Scancode key)
	{
		return kbState_[key] == 1;
	}

	bool isKeyDown(SDL_Keycode key)
	{
		return isKeyDown(SDL_GetScancodeFromKey(key));
	}

	bool isKeyUp(SDL_Scancode key)
	{
		return kbState_[key] == 0;
	}

	bool isKeyUp(SDL_Keycode key)
	{
		return isKeyUp(SDL_GetScancodeFromKey(key));
	}

	// MOUSE EVENTS
	bool mouseMotionEvent()
	{
		return isMouseMotionEvent_;
	}

	bool mouseButtonEvent()
	{
		return isMouseButtonUpEvent_ || isMouseButtonDownEvent_;
	}

	bool mouseButtonUpEvent()
	{
		return isMouseButtonUpEvent_;
	}

	bool mouseButtonDownEvent()
	{
		return isMouseButtonDownEvent_;
	}

	const std::pair<Sint32, Sint32>& getMousePos()
	{
		return mousePos_;
	}

	int getMouseButtonState(uint8_t b)
	{
		assert(b < _LAST_MOUSEBUTTON_VALUE);
		return mbState_[b];
	}

#pragma endregion

private:
	InputHandler()
	{
		// estado del teclado en ese momento -> qué tecla/s se está pulsando
		// devuelve un puntero a un array de key states -> si un elemento del array es 1 PULSADO / 0 NO PULSADO
		kbState_ = SDL_GetKeyboardState(nullptr);


		// limpia estado
		clearState();
	}

#pragma region SETTEA EVENTOS A TRUE
	void onKeyDown(const SDL_Event&)
	{
		isKeyDownEvent_ = true;
	}

	void onKeyUp(const SDL_Event&)
	{
		isKeyUpEvent_ = true;
	}

	void onMouseMotion(const SDL_Event& event)
	{
		isMouseMotionEvent_ = true;
		mousePos_.first = event.motion.x;
		mousePos_.second = event.motion.y;
	}

	void onMouseButtonDown(const SDL_Event& event)
	{
		isMouseButtonDownEvent_ = true;
		switch (event.button.button)
		{
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

	void onMouseButtonUp(const SDL_Event& event)
	{
		isMouseButtonUpEvent_ = true;
		switch (event.button.button)
		{
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

	void handleWindowEvent(const SDL_Event& event)
	{
		switch (event.window.event)
		{
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
	const Uint8* kbState_;
};

// --------
// forma de usar el singleton InputHandler
// InputHandler::instance()->method() / EN VEZ DE ESTO
// ih().method() / ESCRIBIR ESTO
inline InputHandler& ih()
{
	return *InputHandler::instance();
}

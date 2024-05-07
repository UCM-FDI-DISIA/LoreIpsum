#pragma once

//Checkml
#include <game/checkML.h>

#include "../../utils/Vector2D.h"
#include "ComponentUpdate.h"
#include <functional>

// utiliza callbacks funcionales de tipo <void(void)>
using SDLEventCallback = std::function<void(void)>;
class Button : public ComponentUpdate
{
private:
	// ---- ESTADOS ----
	enum ButtonState
	{
		MOUSE_OUT,
		MOUSE_OVER,
		MOUSE_CLICK
	};
	int currentState;

	// ---- CALLBACKS ----
	std::list<SDLEventCallback> callbacks;
	void useCallback() const;

	BoxCollider* myBoxCollider;

public:
	Button();
	~Button();

	void update() override;
	void initComponent() override;
	void connectToButton(SDLEventCallback _callback);

	int getCurrentButtonState() { return currentState; }

	void OnLeftClickDown();
	void OnLeftClickUp();
};


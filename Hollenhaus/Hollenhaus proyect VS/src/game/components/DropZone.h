#pragma once
#include "ComponentUpdate.h"
#include "./basics/BoxCollider.h"
#include "./managers/DrawerManager.h"
#include "./managers/PizarraManager.h"
#include "./Card.h"
#include <functional>

using SDLEventCallback = std::function<void(void)>;
class DropZone : public ComponentUpdate
{
private:
	Vector2D dropZonePos;
	BoxCollider* dropZoneCollider;
	SDLEventCallback callback;

public:

	DropZone();
	~DropZone();

	void initComponent() override;
	void update() override;

	bool isOnDropZone(Transform* cardTransform);

	SDLEventCallback setCallBack(SDLEventCallback _callback) {
		callback = _callback;
		return callback;
	}

	void useCallback() {
		callback();
	}
};
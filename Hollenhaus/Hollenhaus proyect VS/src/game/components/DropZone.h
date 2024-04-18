#pragma once
#include "ComponentUpdate.h"
#include "./basics/BoxCollider.h"
#include "./managers/DrawerManager.h"
#include "./managers/PizarraManager.h"
#include "./Card.h"
#include <functional>

//typedef void (*Callback)(Card*);
using SDLCallbackCards = std::function<void(Card*)>;

class DropZone : public ComponentUpdate
{
private:
	Vector2D dropZonePos;
	BoxCollider* dropZoneCollider;
	SDLCallbackCards callback;

public:
	DropZone();
	~DropZone() override;

	void initComponent() override;
	void update() override;

	bool isOnDropZone(Transform* cardTransform);

	void setCallBack(SDLCallbackCards cb)
	{
		callback = cb;
	}

	void useCallback(Card* card)
	{
		if (callback)
			callback(card);
	}
};

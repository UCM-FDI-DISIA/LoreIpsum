#pragma once
#include "ComponentUpdate.h"

class Vector2D;

class DropDetector :
	public ComponentUpdate
{
public:
	DropDetector();
	~DropDetector() override;

	void initComponent() override;
	void update() override;

private:
	bool ocuped = false;

	Vector2D cardPos;

	Vector2D boardPos;

public:
	void setOcuped(bool b) { ocuped = b; }

	bool isOcuped() { return ocuped; }

	Vector2D& getCardPos() { return cardPos; };

	Vector2D& getBoardPos() { return boardPos; };

	int getBoardPosX() { return boardPos.getX(); }
	int getBoardPosY() { return boardPos.getY(); }
};

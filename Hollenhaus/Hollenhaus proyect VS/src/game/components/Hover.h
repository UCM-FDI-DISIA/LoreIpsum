﻿#pragma once
#include "ComponentUpdate.h"

constexpr int HOVER_SPEED = 30,
              HOVER_TIMER = 500,
              HOVER_SCALE = 2,
              HOVER_LAYER = 999;
const Vector2D HOVER_OFFSET = {-20, -20};

class Hover : public ComponentUpdate
{
	/// hover values
	int hoverScale = HOVER_SCALE; // escala durante el hover
	int hoverLayer = HOVER_LAYER;
	Vector2D hoverOffset = HOVER_OFFSET; // distancia desde la posicion inicial al hacer hover

	/// initial values
	Vector2D iniScale; // escala inicial
	Vector2D iniPos; // pos inicial
	int iniLayer; // layer inicial

	/// component access
	SpriteRenderer* spr = nullptr;
	Transform* tr = nullptr;
	BoxCollider* bc = nullptr;

	/// tweeny
	tweeny::tween<float> hoverTweenX;
	tweeny::tween<float> hoverTweenY;

	/// timer
	int hoverTimer = 0;
	int hoverActivationSpeed = HOVER_TIMER;

	/// sentido de la animacion
	bool intoHover = false;
	bool outoHover = false;
	int hoverSpeed = HOVER_SPEED;
	bool isOnHand = false;

	void resetTweensForward();
	void resetTweensBackward();
	
	void onHoverEnter();
	void onHoverExit();
public:
	Hover() = default;

	//Hover(int scale, int layer, const Vector2D& offset = HOVER_OFFSET, int actSpeed = HOVER_TIMER, int hoverSpeed = 30)
	//	: hoverScale(scale), hoverLayer(layer), hoverOffset(offset), iniLayer(1),
	//	  hoverActivationSpeed(actSpeed), hoverSpeed(hoverSpeed)
	//{
	//}

	~Hover() override = default;
	void initComponent() override;
	void update() override;
	void setOnHand(bool value) { isOnHand = value; }

};

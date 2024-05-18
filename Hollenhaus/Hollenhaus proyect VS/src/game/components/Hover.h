#pragma once
#include "ComponentUpdate.h"

constexpr int HOVER_TIMER = 500,
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

	/// tweeny
	tweeny::tween<double> hoverTween;

	/// timer
	int hoverTimer = 0;

	//hoverTween =
	//	tweeny::from(fanY - 10)
	//	.to(fanY + 5)
	//	.to(fanY - 10)
	//	.during(30)
	//	.via(tweeny::easing::sinusoidalInOut);

public:
	Hover() = default;
	Hover(int scale, int layer, const Vector2D& offset)
	: hoverScale(scale), hoverLayer(layer), hoverOffset(offset)
	{}
	~Hover() override = default;
	void initComponent() override;
	void update() override;
	void onHoverEnter();
	void onHoverExit();
};

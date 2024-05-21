#pragma once
#include "ComponentUpdate.h"
#include "HandComponent.h"

constexpr int HOVER_SPEED = 30,
              HOVER_TIMER = 750,
              HOVER_LAYER = 999;
constexpr float HOVER_SCALE = 1.4f;
const Vector2D HOVER_OFFSET = {-70, -250};

class Hover : public ComponentUpdate
{
	/// hover values
	float hoverScale = HOVER_SCALE; // escala durante el hover
	int hoverLayer = HOVER_LAYER;
	Vector2D hoverOffset = HOVER_OFFSET; // distancia desde la posicion inicial al hacer hover

	/// initial values
	Vector2D iniScale; // escala inicial
	Vector2D iniPos; // pos inicial
	int iniLayer; // layer inicial

	/// component access
	SpriteRenderer* spr = nullptr;
	Transform* tr = nullptr;
	HandComponent* hc = nullptr;

	/// tweeny
	tweeny::tween<float> hoverTweenX;
	tweeny::tween<float> hoverTweenY;
	tweeny::tween<float> scaleTween;

	/// timer
	int hoverTimer = 0;
	int hoverActivationSpeed = HOVER_TIMER;

	/// sentido de la animacion
	bool intoHover = false;
	bool outoHover = false;
	int hoverSpeed = HOVER_SPEED;
	bool isOnHand = false;
	bool hasClicked = false;

	void resetTweensForward();
	void resetTweensBackward();
	
	void onHoverEnter();
	void onHoverExit();

	void updateEveryComponent();
	void resetEveryComponent();

	bool checkTweenConstraints();
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
	void setHandComponent(HandComponent* h) { hc = h; }
	void setIniPos(const Vector2D& v) { iniPos = v; }
	void setIniScale(const Vector2D& v) { iniScale = v; }
};

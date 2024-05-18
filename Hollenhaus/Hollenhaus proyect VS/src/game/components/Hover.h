#pragma once
#include "ComponentUpdate.h"

constexpr int HOVER_SCALE = 2,
			  HOVER_LAYER = 999;
const Vector2D HOVER_OFFSET = {-20, -20};

class Hover : public ComponentUpdate
{
	/// hover values
	int hoverScale = HOVER_SCALE; // escala durante el hover
	Vector2D hoverOffset; // distancia desde la posicion inicial al hacer hover
	int hoverLayer = HOVER_LAYER;

	/// initial values
	Vector2D iniScale; // escala inicial
	Vector2D iniPos; // pos inicial
	int iniLayer; // layer inicial

	/// component access
public:
	Hover() = default;
	~Hover() override = default;
	void initComponent() override;
	void update() override;
};

#pragma once

#include <vector>
#include <string>

#include "../ComponentUpdate.h"

class Transform;
class Vector2D;

constexpr int NUMBER_OF_KEYS = 6;

class KeyManager :
	public ComponentUpdate
{
public:
	KeyManager();

	void initComponent() override;

	// Anyade una descripcion a la leyenda
	void addKey();

private:
	int addToY_;

	int lastKey_;

	// Vector de nombres de iconos
	std::vector<std::string> keyNames_;
	// Vector de descripciones
	std::vector<std::string> descs_;
	// Vector de entidades icono + desc, 1. Imagen / 2. Texto
	std::vector<std::pair<ecs::entity_t, ecs::entity_t>> keys_;

	Transform* tr_;
	Vector2D pos_;

	std::string font_;
};

#pragma once
#include "game/Card.h"
#include "Cell.h"

namespace Effects
{
	enum Type
	{
		Esquina,
		Centro,
		Flecha,
		Superflecha,
		Block,
		Unblockable,

		_NO_DISCARD_
	};
}

class EffectCollection
{
public:
	EffectCollection();

	// ---- TIPOS DE EFECTOS ----
	// añade valor a algunas o todas sus adyacentes
	static void addAdj(Cell* cell, CellData::Direction direction, int add, bool ultimateArrow);
	static void addSimpleAdj(Cell* cell, CellData::Direction direction, int add);
	static void addSuperAdj(Cell* cell, CellData::Direction direction, int add);

	// añade valor a la propia carta si esta en centro - si el número de cartas a izq/der/arr/abj son el mismo
	static void addCenter(Cell* cell, int add);

	// añade valor a la propia carta si esta en esquina - si solo tiene dos casilla adyacentes en cualquier dir
	static void addCorner(Cell* cell, int add);

	// bloquea el efecto de la carta en alguna direccion
	static void blockCard(Cell* cell, CellData::Direction direction);

	// indica que esta carta no se puede bloquear
	static void unblockable(Cell* cell, bool isUnblockable);


	/// En funcion del indice, devuelve el callback del efecto
	///	*** Esto es terrible, quiero que sirva para salir al paso
	///	y como concepto inicial ***
	static std::function<void()> getEffect(
		Effects::Type index,
		Card* card,
		int value,
		CellData::Direction direction)
	{
		switch (index)
		{
		case Effects::Esquina:
			return [card, value]
			{
				addCorner(card->getCell(), value);
			};
		case Effects::Centro:
			return [card, value]
			{
				addCenter(card->getCell(), value);
			};
		case Effects::Flecha:
			return [card, direction, value]
			{
				addSimpleAdj(card->getCell(), direction, value);
			};
		case Effects::Superflecha:
			return [card, direction, value]
			{
				addSuperAdj(card->getCell(), direction, value);
			};
		case Effects::Block:
			return [card, direction]
			{
				blockCard(card->getCell(), direction);
			};
		case Effects::Unblockable:
			return [card]
			{
				unblockable(card->getCell(), card->getUnblockable());
			};
		default:
			return nullptr;
		}
	}
};

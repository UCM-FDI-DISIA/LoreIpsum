#include <../pchs/pch.h>


#include "Manager.h"


namespace ecs
{
	// reserva suficiente (?) memoria para evitar el redimensionamiento
	// del vector de entidades
	Manager::Manager() : entsByGroup_()
	{
		for (auto& ents : entsByGroup_)
		{
			ents.reserve(100);
		}
	}

	//borra todas las entidades
	Manager::~Manager()
	{
		Free();
	}

	void Manager::Free()
	{
		for (auto& ents : entsByGroup_)
		{
			for (auto& e : ents)
			{
				setAlive(e, false);
			}
		}
		ordenRendering.clear();
		refresh();
	}

	//Su objetivo es borrar todas las entidades muertas, es
	//decir las que han salido del juego en la última iteración
	void Manager::refresh()
	{
		for (auto& ents_ : entsByGroup_)
		{
			ents_.erase(
				//Para cada elemento de ents_, remove_if llama a la función
				//(lambda expression) para decider si borrarlo o no, aprovechamos
				//para liberar la memoria también
				std::remove_if(ents_.begin(), ents_.end(), [this](Entity* e)
				{
					if (isAlive(e))
					{
						return false;
					}
					DeleteEntityMap(e->getLayer(), e);
					delete e;
					return true;
				}),
				ents_.end());
		}
	}
}

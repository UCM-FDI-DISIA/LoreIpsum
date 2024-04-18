#pragma once

class Entity;
class Manager;

namespace ecs
{
	class Component
	{
	public:
		Component() :
			ent_(),
			mngr_()
		{
		}

		virtual ~Component()
		{
		};

		// Para pasarle un puntero a su entidad
		void setContext(Entity* ent, Manager* mngr)
		{
			ent_ = ent;
			mngr_ = mngr;
		}

		// Se invoca al anyadir un componente a una entidad.
		// Para inicializar el componenete si es necesario.
		virtual void initComponent()
		{
		};

		Entity* getEntity() { return ent_; }
		void enable(bool value) { enabled_ = value; }
		bool isEnabled() const { return enabled_; }

	protected:
		//puntero a la entidad a la que pertenece el componente
		Entity* ent_;
		Manager* mngr_;
		bool enabled_ = true;

		friend Manager;
	};
}

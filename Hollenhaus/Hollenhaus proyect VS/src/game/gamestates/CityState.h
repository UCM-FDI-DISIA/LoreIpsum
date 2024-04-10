#include "GameState.h"

class Factory;

class CityState : public GameState
{
public:

	CityState(); //Constructora

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;
private:

	//Velocidad del fondo (mov)
	//Input para mover el fondo
	//Cambio a tienda y oficina
	//Cambio a NPC
	//Dialogo NPC -> Cambio estado combate
	ecs::entity_t fondo;
	ecs::entity_t fantasmiko;
	Factory* factory;

	// tween fantasmiko
	tweeny::tween<float> tweensy;
};

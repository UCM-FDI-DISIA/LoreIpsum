#include "GameState.h"
#include "../../utils/tweeny-3.2.0.h"

class Factory;

class CityState : public GameState
{
public:

	CityState(); //Constructora
	~CityState();

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

	void onPause();

private:

	//Velocidad del fondo (mov)
	//Input para mover el fondo
	//Cambio a tienda y oficina
	//Cambio a NPC
	//Dialogo NPC -> Cambio estado combate
	ecs::entity_t fondo;
	ecs::entity_t fantasmiko;
	ecs::entity_t fade;
	Factory* factory;

	// tween fantasmiko
	tweeny::tween<float> fantastween;
	tweeny::tween<int> fadetween;
};

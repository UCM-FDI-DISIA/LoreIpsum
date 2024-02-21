#include "GameState.h"
class CityState : public GameState
{
public:
	void update() override;
	void render() const override;
	void refresh() override;
	bool onEnter();
	bool onExit();
private:

	//Velocidad del fondo (mov)
	//Input para mover el fondo
	//Cambio a tienda y oficina
	//Cambio a NPC
	//Dialogo NPC -> Cambio estado combate
};

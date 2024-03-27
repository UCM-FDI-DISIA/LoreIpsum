#pragma once
#include <list>

class ShopComponent : public ComponentUpdate
{public:

	ShopComponent();
	~ShopComponent();

	//------Inicializacion del componente:
	void initComponent() override;

	//------Genera las 4 cartas que puede comprar el jugador:
	void generateCards();
	//------Comprueba si una carta ha sido comprada por el jugador, es decir, esta en el drawer (cajon):
	bool checkCardIsBought(int id);

private:
	//----Guarda las 4 cartas de la tienda.
	int* shopCards; 
	



};


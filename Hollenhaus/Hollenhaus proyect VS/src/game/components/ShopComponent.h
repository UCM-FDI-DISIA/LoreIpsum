#pragma once

#include <list>

// Cantidad de cartas de la tienda.
const int CARDS_IN_SHOP = 4;

class Card;
class Button;

class ShopComponent : public ComponentUpdate
{public:

	ShopComponent();
	~ShopComponent();

	//------Inicializacion del componente.
	void initComponent() override;

	//------Genera las CARDS_IN_SHOP cartas que puede comprar el jugador.
	void generateCards();
	//------Comprueba si una carta ha sido comprada por el jugador, es decir, esta en el drawer (cajon).
	bool checkCardIsBought(int id);
	//------Muestra las cartas disponibles para comprar.
	void showCards();
	//------Muestra los precios de las cartas.
	void showPrizes();
	void setButtons();
	void buyCard();
	bool confirmPurchase();

	void onLeftClick();

private:
	//----Guarda las CARDS_IN_SHOP cartas de la tienda.
	int* shopCards; 
	//----Precio de las cartas.
	int* shopCardsPrize;
	//----Guarda las posiciones de las cartas.
	Vector2D* shopCardsPositions;
	//----Guarda las cartas creadas para luego interactuar con ellas.
	std::list<Card*> buyableCards;
	//----Guarda los botones para luego poder acceder a la entidad del boton clickado.
	std::list<Button*> buttons;
	//----Dinero del jugador:
	int money;
	//------------------------------lo del precio de las cartas deberia de estar en el json. Todas en el mismo json.
	//------------------------------array de precios de las cartas. Sus posiciones son las de las cartas pero bajando la y.
	
};


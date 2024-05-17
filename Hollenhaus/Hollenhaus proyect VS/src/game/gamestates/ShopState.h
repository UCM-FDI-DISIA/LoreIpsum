#pragma once

//Checkml
#include <game/checkML.h>

#include "GameState.h"
#include <vector>

const int COIN_VALUE = 100; // Valor de cada moneda.
const int MIN_Y_POS = 490; // Minima posicion de Y donde  puede aparecer una moneda.
const int MAX_Y_POS = 550; // Maxima posicion en Y donde puede aparecer una moneda.
const int MIN_X_POS = 200; // Minima posicion de X donde  puede aparecer una moneda.
const int MAX_X_POS = 600; // Maxima posicion en X donde puede aparecer una moneda.


class Factory;
class RandomNumberGenerator;

class ShopState : public GameState
{
public:
	// Constructora.
	ShopState();
	ShopState(bool a);

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;


	void onPauseSH();


	//----Metodo que se llamada desde el ShopComponent cuando una carta se selecciona para que se ilumninen las monedas correspondientes.
	void cardSelected(int prize) override;
	//----Metodo que se llamada desde el ShopComponent cuando se compra o no una carta para que se dejen de iluminar monedas y para resetear su cantidad dependiendo del dinero del jugador.
	void deSelected() override;
	//----Hace que nCoins se iluminen.
	void shine(int nCoins);

	ecs::entity_t createCard(int id, Vector2D pos) override;

	//----Dada una moneda cambia su textura para que se ilumnine.
	void showCoin(ecs::entity_t coinToShow);
	//----Dada una moneda cambia su textura para que se deje de iluminar.
	void hideCoin(ecs::entity_t coinToHide);

	//----Settea el manager de la decision de comprar.
	void setDecisionManager();

	//----Crea las monedas al principio al entrar al estado.
	void createCoins();
	//----Crea una moneda.
	ecs::entity_t createCoin(int x, int y);
	//----Resetea el numero de monedas en la mesa.
	void updateCoins();


private:
	Factory* factory;

	ecs::entity_t manager; // Manager de la decision de comprar.
	RandomNumberGenerator& rand_; // Para generar numeros aleatorios.

	//examen ig 3 horas.
	//teoria : esto hace tal eso hace eso, textura hace nsq. relacionado con la infomatica grafica.pipeline, vistas... 30
	//pratica : la practica como base. 70
	// simulacro de examen el dia 8.
	// hace falta aprobar las dos partes para poder aprobar.

		//---Tutorial

	bool isTutorial = false;

	ecs::entity_t base;             // entidad para colocar los popups, se va moviendo segun donde los queramos
	ecs::entity_t tutorial;
	std::vector<ecs::entity_t> objs;

	// -------------- tutorial --------------------
	void setTutorial();
	void prepareTutorial();
	void startTutorial(bool a);

};


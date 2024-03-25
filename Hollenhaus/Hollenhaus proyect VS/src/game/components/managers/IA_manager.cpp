#include "pch.h"
#include "IA_manager.h"

#include "../../../utils/Vector2D.h"
#include <vector>

#include "../Card.h"
#include "Manager.h"


class State {
	std::vector<std::vector<Card*>> _board;

	std::vector<Card*> playerHand;
	std::vector<Card*> enemyHand;

	std::vector<Card*> playerDeck;
	std::vector<Card*> enemyDeck;

	int actionPoints;

	//TuplaSolucion();

};

struct CartaColocada {

	CartaColocada(int indice, Vector2D pos)
		:indice(indice), pos(pos) {};

	int indice;//indice en la mano
	Vector2D pos;//posicon en el tablero (-1,-1) no se coloca
};

struct TuplaSolucion {
	int cartasRobadas;
	std::vector<CartaColocada> cartas;//hand + cartas robadas	
};

std::vector<TuplaSolucion> calcularTurno(
	int puntosAccion,
	std::vector<Card*>& Hand,
	std::vector<Card*>& deck,
	std::vector<std::vector<bool>>& _board) {

	std::vector<TuplaSolucion> solucionesGlobal;
	/*
	for (robar carta)
	{
		draw(i);

		//actualizar solucionActual
		//act puntosRestantes

		posiblesTurnos(solciones)//hand + cartas robadas	

			//actualizar la lista de soluciones global(TuplaSolucion)

			int j;
		for (soluciones) solucionesGlobal.add(TuplaSolucion{ i,soluciones[j] })

			//desactualizar solucion Actual
	}

	*/

	return solucionesGlobal;
}


void posiblesTurnos(
	int cartaActual, int nCartas,
	std::vector<std::vector<CartaColocada>>& soluciones,
	std::vector<CartaColocada>& solAct, 
	int puntosRestantes,
	const std::vector<Card*>& playerHand,//mano del jugador, ref const
	std::vector<std::vector<bool>>& _board // true si ocupada, false si libre
)
{
	if (cartaActual == nCartas ) {
		soluciones.push_back(solAct);
		return;
	}

	//asumiendo que los tableros son rectangulares
	int sizeX = _board.size();
	int sizeY = _board[0].size();

	bool esValida = true;

	//si la carta cuesta mas puntos de los que me quedan
	if (playerHand[cartaActual]->getCost() > puntosRestantes) {
		esValida = false;
	}

	if (esValida) {

		for (int i = 0; i < sizeX; i++) {

			for (int j = 0; j < sizeY; j++) {

				//si casilla no ocupada
				if (!_board[i][j]) {


					//actualizar solAct
					_board[i][j] = true;
					solAct.push_back(CartaColocada(cartaActual,Vector2D(i,j)));

					puntosRestantes -= playerHand[cartaActual]->getCost();

					//siguiente nivel
					posiblesTurnos(cartaActual + 1, nCartas, soluciones, solAct, puntosRestantes,
						playerHand, _board);

					//desactualizar solucion Actual	
					solAct.pop_back();
					_board[i][j] = false;

					puntosRestantes += playerHand[cartaActual]->getCost();

				}

			}
		}

	}

	//actualizar solucion actual con (-1,-1) No colocar	
	solAct.push_back(CartaColocada(cartaActual, Vector2D(-1,-1)));

	//siguiente nivel
	posiblesTurnos(cartaActual + 1, nCartas, soluciones, solAct, puntosRestantes,
		playerHand, _board);

	//desactualizar solucion Actual	
	solAct.pop_back();

}

IA_manager::IA_manager()
{
}

IA_manager::~IA_manager()
{
}

void IA_manager::initComponent()
{
}

void IA_manager::update()
{
}

void IA_manager::evaluateState()
{
	std::vector<std::vector<CartaColocada>> soluciones;
	std::vector<CartaColocada> solAct;
	int puntosRestantes = 4;
	std::vector<Card*> playerHand;
	std::vector<std::vector<bool>> _board;

	Card* a = new Card(5, -1);
	Card* b = new Card(5, -1);
	Card* c = new Card(5, -1);

	playerHand.push_back(a);
	playerHand.push_back(b);
	playerHand.push_back(c);

	std::vector<bool> aux{ false,false,false };

	_board.push_back(aux);
	_board.push_back(aux);
	_board.push_back(aux);

	posiblesTurnos(0, 3, soluciones, solAct, puntosRestantes, playerHand, _board);


	TuVieja("TURNO: \n");

	for (auto& s : soluciones) {
		for (auto& c :s) {
			std::cout << "I: " << c.indice << " P: " << c.pos.getX() << "," << c.pos.getY() << std::endl;
		}
	}

	TuVieja("TURNO ACABADO \n");
}

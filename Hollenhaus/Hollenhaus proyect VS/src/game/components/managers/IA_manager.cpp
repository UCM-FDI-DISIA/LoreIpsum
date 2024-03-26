#include "pch.h"
#include "IA_manager.h"

#include "vector"
#include "iostream"

#include "../Card.h"
#include "../../Namespaces.h"
#include <SDL.h>


IA_manager::IA_manager(){}

IA_manager::~IA_manager(){}

void IA_manager::initComponent(){}

void IA_manager::update(){}

void IA_manager::evaluateState()
{

	State s;
	s.actionPoints = 4;
	s.playerDeck;
	s.playerHand;
	s._boardBools;

#pragma region Mano y mazo de pruebas


	Card* a = new Card(2, -1);
	Card* b = new Card(1, -1);
	Card* c = new Card(0, -1);

	Card* m1 = new Card(1, -1);
	Card* m2 = new Card(0, -1);
	Card* m3 = new Card(2, -1);
	Card* m4 = new Card(1, -1);
	Card* m5 = new Card(1, -1);

	s.playerDeck.push_back(m1);
	s.playerDeck.push_back(m2);
	s.playerDeck.push_back(m3);
	s.playerDeck.push_back(m4);
	s.playerDeck.push_back(m5);


	s.playerHand.push_back(a);
	s.playerHand.push_back(b);
	s.playerHand.push_back(c);

	std::vector<bool> aux{ false,false,false };

	s._boardBools.push_back(aux);
	s._boardBools.push_back(aux);
	s._boardBools.push_back(aux);
	s._boardBools.push_back(aux);
#pragma endregion

	State* best = nullptr;

	uint32_t time = SDL_GetTicks();

	minimax(0, 1, true, s, best);
	time = SDL_GetTicks() - time;
	std::cout << time << std::endl;


#if _DEBUG
	/*
	TuVieja("TURNO: \n");

	
	for (auto& s : soluciones) {
		std::cout << "R: " << s.cartasRobadas << std::endl;
		for (auto& c :s.cartas) {
			std::cout << " I: " << c.indice << " P: " << c.pos.getX() << "," << c.pos.getY() << std::endl;
		}
	}
	

	TuVieja("TURNO ACABADO \n");

	*/
#endif // _DEBUG

	//s.apply(soluciones[21], true);

	//auto x = all_posible_next_states(s, true);

}



void IA_manager::posiblesTurnos(
	int cartaActual, int nCartas,
	std::vector<std::vector<CartaColocada>>& soluciones,
	std::vector<CartaColocada>& solAct,
	int puntosRestantes,
	const std::vector<Card*>& playerHand,//mano del jugador, ref const
	std::vector<std::vector<bool>>& _board // true si ocupada, false si libre
)
{
	//si estoy en la ultima carta, añado la solucion a la lista
	if (cartaActual == nCartas) {
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

	//si puedo colocar la carta, miro todas las casillas
	if (esValida) {

		//recorrido para cada casilla
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {

				//si casilla no ocupada
				if (!_board[i][j]) {

					//actualizar solAct
					_board[i][j] = true;
					solAct.push_back(CartaColocada(cartaActual, Vector2D(i, j)));
					puntosRestantes -= playerHand[cartaActual]->getCost();

					//siguiente nivel
					posiblesTurnos(cartaActual + 1, nCartas, soluciones, solAct, puntosRestantes,
						playerHand, _board);

					//desactualizar solAct
					solAct.pop_back();
					_board[i][j] = false;
					puntosRestantes += playerHand[cartaActual]->getCost();

				}
			}
		}
	}

	//actualizar solucion actual con (-1,-1) No colocar	
	solAct.push_back(CartaColocada(cartaActual, Vector2D(-1, -1)));

	//siguiente nivel
	posiblesTurnos(cartaActual + 1, nCartas, soluciones, solAct, puntosRestantes,
		playerHand, _board);

	//desactualizar solucion Actual	
	solAct.pop_back();
}


std::vector<IA_manager::TuplaSolucion> IA_manager::calcularTurno(State s, bool isPlayer) {

	std::vector<TuplaSolucion> allPosiblePlays;

	int i = 0;

	//NOTA: si cambia el coste del robo hay que cambiar esto

	//la cantidad de veces que se puede robar es el minimo entre los puntos de accion y el tamaño del mazo
	int nRobosPosibles = fmin(s.actionPoints, 
		isPlayer ? s.playerDeck.size() : s.enemyDeck.size());

	auto& currentDeck = isPlayer ? s.playerDeck : s.enemyDeck;
	auto& currentHand = isPlayer ? s.playerHand : s.enemyHand;

	while (i <= nRobosPosibles)
	{
		//si toca robar
		if (i > 0) {
			//robar carta
			Card* c = currentDeck.back();

			currentDeck.pop_back();
			currentHand.push_back(c); 
		
			s.actionPoints--;//- N coste de robar carta
		}

		//actualizar solucionActual
		//act puntosRestantes
		std::vector<std::vector<CartaColocada>> partialPlays;
		std::vector<CartaColocada> solAct;

		//obtener las jugadasParciales
		posiblesTurnos(0, currentHand.size(), partialPlays, solAct, s.actionPoints,
			currentHand, s._boardBools);//hand + cartas robadas	

		//actualizar la lista de jugadasTotales(TuplaSolucion)
		for (auto& s : partialPlays) {
			allPosiblePlays.push_back(TuplaSolucion{ i,s });
		}

		i++;
	}

	return allPosiblePlays;
}

std::vector<IA_manager::State> IA_manager::all_posible_next_states(const State& s,bool isPlayer) {

	std::vector<State> allStates;

	//dado un estado, aplicamos todas las posible jugadas y generamos todos los posibles futuros estados
	for (auto& jugada : calcularTurno(s, isPlayer)) {
		State nuevo = s;//copia del estado
		nuevo.apply(jugada, isPlayer);//aplicar jugada
		allStates.push_back(nuevo);//añadir a la lista
	}

	return allStates;
}

int IA_manager::minimax(int depth,int h, bool isPlayer, const State& current_state, State*& best) {

	//si alcanza la profundidad indicada, devuelve el valor de la heurisitca
	if (depth == h) { return current_state.heuristic(); }
	
	int bestValue = 0;

	for (State& s : all_posible_next_states(current_state, isPlayer)) {
		
		int current = minimax(depth + 1, h, !isPlayer, s,best);

		if (isPlayer && current > bestValue) { //si es jugador, maximiza el valor			
			bestValue = current;
			best = new State(s);		
		}
		else if (current < bestValue) {//si es la IA, lo minimiza
			bestValue = current;
			best = new State(s);
		}	
	}

	return bestValue;
}

#include "pch.h"
#include "IA_manager.h"

#include "vector"
#include "iostream"

#include "../Card.h"
#include "../../Namespaces.h"
#include <SDL.h>


struct CartaColocada {

	CartaColocada() {};

	CartaColocada(int indice, Vector2D pos)
		:indice(indice), pos(pos) {};

	int indice;//indice en la mano
	Vector2D pos;//posicon en el tablero (-1,-1) no se coloca
};

struct TuplaSolucion {

	TuplaSolucion(int cartasRobadas, std::vector<CartaColocada> cartas)
		: cartasRobadas(cartasRobadas), cartas(cartas) {};
	TuplaSolucion() {};

	int cartasRobadas;
	std::vector<CartaColocada> cartas;//hand + cartas robadas	
};

struct State {

	State() {
		
		std::vector<Card*> cards{ nullptr,nullptr,nullptr };
		std::vector<Players::Owner> owners{ Players::NONE,Players::NONE,Players::NONE };

		for (int i = 0; i < 4; i++) {
			_boardCards.push_back(cards);
			_boardOwners.push_back(owners);
		}
		
	};

	std::vector<std::vector<bool>> _boardBools;
	std::vector<std::vector<Card*>> _boardCards;
	std::vector<std::vector<Players::Owner>> _boardOwners;

	std::vector<Card*> playerHand;
	std::vector<Card*> enemyHand;

	std::vector<Card*> playerDeck;
	std::vector<Card*> enemyDeck;

	int actionPoints;

	TuplaSolucion _jugada;

	//devuelve la diferencia de puntos entre el jugador y el enemigo 
	//PuntosJugador -PuntosEnemigo
	// el valor es positivo si el jugador tiene mas puntos, y negativo si tiene menos
	int heuristic() const { 
		return 1;
	};

	void apply(TuplaSolucion jugada,bool isPlayer) {

		//guardar la jugada que lleva a este estado
		_jugada = jugada;

		int nCartasColocadas = 0;

		if (isPlayer) {

			//robarCartas
			for (int i = 0; i < jugada.cartasRobadas; i++) {

				Card* c = playerDeck.back();
				playerDeck.pop_back();

				playerHand.push_back(c);
			}


			//poner cartas en el mazo
			for (int i = 0; i < jugada.cartas.size(); i++) {
			
				//si se coloca la carta
				if (jugada.cartas[i].pos.getX() != -1) {

					int posX = jugada.cartas[i].pos.getX();
					int posY = jugada.cartas[i].pos.getY();
					
					//poner la carta en el tablero
					_boardBools[posX][posY] = true;
					_boardOwners[posX][posY] = Players::PLAYER1;
					_boardCards[posX][posY] = playerHand[(i - nCartasColocadas)];

					//quitar la carta de la mano
					playerHand.erase(playerHand.begin() + (i - nCartasColocadas));

					nCartasColocadas++;
				}

			}

		}
		else {
			//robarCartas
			for (int i = 0; i < jugada.cartasRobadas; i++) {

				Card* c = enemyDeck.back();
				enemyDeck.pop_back();

				enemyHand.push_back(c);
			}

			//poner cartas en el mazo
			for (int i = 0; i < jugada.cartas.size(); i++) {

				//si se coloca la carta
				if (jugada.cartas[i].pos.getX() != -1) {

					int posX = jugada.cartas[i].pos.getX();
					int posY = jugada.cartas[i].pos.getY();

					//poner la carta en el tablero
					_boardBools[posX][posY] = true;
					_boardOwners[posX][posY] = Players::PLAYER2;
					_boardCards[posX][posY] = playerHand[(i - nCartasColocadas)];

					//quitar la carta de la mano
					enemyHand.erase(enemyHand.begin() + (i - nCartasColocadas));

					nCartasColocadas++;

				}

			}


		}

	}
};


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

std::vector<TuplaSolucion> calcularTurno(State s,bool isPlayer) {

	std::vector<TuplaSolucion> solucionesGlobal;

	int i = 0;

	int aux = s.actionPoints;


	//la cantidad de veces que se puede robar es el minimo entre los puntos de accion y el tamaño del mazo
	if (isPlayer) {
		aux = fmin(s.actionPoints, s.playerDeck.size());
	}
	else {
		aux = fmin(s.actionPoints, s.enemyDeck.size());
	}

	while(i <= aux)
	{
		if (i > 0) {
			if (isPlayer) {
				//robar carta
				Card* c = s.playerDeck.back();

				s.playerDeck.pop_back();
				s.playerHand.push_back(c);
			}
			else {
				//robar carta
				Card* c = s.enemyDeck.back();

				s.enemyDeck.pop_back();
				s.enemyHand.push_back(c);
			}
			s.actionPoints--;//- N coste de robar carta
		}

		//actualizar solucionActual
		//act puntosRestantes

		std::vector<std::vector<CartaColocada>> soluciones;
		std::vector<CartaColocada> solAct;

		if (isPlayer) {
			posiblesTurnos(0, s.playerHand.size(), soluciones, solAct, s.actionPoints,
				s.playerHand, s._boardBools );//hand + cartas robadas	
		}
		else {
			posiblesTurnos(0, s.enemyHand.size(), soluciones, solAct, s.actionPoints,
				s.enemyHand, s._boardBools);//hand + cartas robadas	
		}

		//actualizar la lista de soluciones global(TuplaSolucion)

		int j = 0;
		for (auto& s : soluciones) {
			solucionesGlobal.push_back(TuplaSolucion{ i,s });
		}

		i++;
	}

	return solucionesGlobal;
}

std::vector<State> all_posible_next_states(const State& s, bool isPlayer);

int minimax(int depth, int h, bool isPlayer, const State& current_state, State*& best);

IA_manager::IA_manager()
{
}

IA_manager::~IA_manager()
{
}

void IA_manager::initComponent()
{
}

void IA_manager::update(){
}

void IA_manager::evaluateState()
{

	State s;
	s.actionPoints = 4;
	s.playerDeck;
	s.playerHand;
	s._boardBools;

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
	
	uint32_t time = SDL_GetTicks();

	//std::vector<TuplaSolucion> soluciones = calcularTurno(s,true);

	State* best = nullptr;

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



std::vector<State> all_posible_next_states(const State& s,bool isPlayer) {
	std::vector<State> allStates;

	for (auto& jugada : calcularTurno(s, isPlayer)) {
		State nuevo = s;
		nuevo.apply(jugada, isPlayer);
		allStates.push_back(nuevo);
	}


	return allStates;
}



int minimax(int depth,int h, bool isPlayer, const State& current_state,State*& best) {

	//si alcanza la profundidad indicada, devuelve el valor de la heurisitca
	if (depth == h) {
		return current_state.heuristic();
	}

	int value = 0;
	//State* best = nullptr;

	for (State& s : all_posible_next_states(current_state, isPlayer)) {
		int current = minimax(depth + 1, h, !isPlayer, s,best);

		if (isPlayer) {
			if (current > value) {
				value = current;
				best = new State(s);
			}
		}
		else {
			if (current < value) {
				value = current;
				best = new State(s);

			}
		}
	}



	return 0;
}
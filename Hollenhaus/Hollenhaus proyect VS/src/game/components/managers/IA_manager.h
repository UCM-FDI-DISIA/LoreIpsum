#pragma once

#include "../ComponentUpdate.h"

#include "../../../utils/Vector2D.h"
//#include "../../../utils/tweeny-3.2.0.h"
#include <array>

class Card;
class BoardManager;
class HandComponent;
class DeckComponent;
class MatchManager;


class IA_manager : public ComponentUpdate
{
public:

	#pragma region Structs internos

	struct CartaColocada {

		//constructoras
		CartaColocada() {};
		CartaColocada(int indice, Vector2D pos)
			:indice(indice), pos(pos) {};

		int indice;//indice en la mano
		Vector2D pos;//posicon en el tablero (-1,-1) no se coloca
	};

	struct InfoJugada {

		//constructoras
		InfoJugada() {};
		InfoJugada(int cartasRobadas, std::vector<CartaColocada> cartas)
			: cartasRobadas(cartasRobadas), cartas(cartas) {};

		int cartasRobadas;
		std::vector<CartaColocada> cartas;//hand + cartas robadas	
	};

	struct State {
		
		static IA_manager* ia_manager ;

		//constructora(inicializa los tableros)
		State() {

			int N = 4;//boardSize

			//inicializacion de los tableros
			std::vector<Card*> cards(N, nullptr);
			std::vector<Players::Owner> owners(N,Players::NONE);
			std::vector<bool> bools(N,false);

			for (int i = 0; i < N; i++) {
				_boardCards.push_back(cards);
				_boardOwners.push_back(owners);
				_boardBools.push_back(bools);
			}
		};


		~State() {

			for (auto& e : playerHand) {
				if (e == nullptr) continue;
				delete e;
				e = nullptr;
			}
		
			for (auto& e : enemyHand) {		
				if (e == nullptr) continue;
				//delete e;
				//e = nullptr;
			}
			

		}

		//varios tableros para representar el estado 
		std::vector<std::vector<bool>> _boardBools;
		std::vector<std::vector<Card*>> _boardCards;
		std::vector<std::vector<Players::Owner>> _boardOwners;

		//mano del jugador y enemigo
		std::vector<Card*> playerHand;
		std::vector<Card*> enemyHand;

		//mazo del jugador y enemigo
		std::vector<Card*> playerDeck;
		std::vector<Card*> enemyDeck;


		int actionPoints;

		InfoJugada _jugada;

		//devuelve la diferencia de puntos entre el jugador y el enemigo 
		//PuntosJugador -PuntosEnemigo
		// el valor es positivo si el jugador tiene mas puntos, y negativo si tiene menos
		int heuristic() {
			return ia_manager->heuristic(this);
		};

		//aplica una jugada al estado
		void apply(InfoJugada jugada, bool isPlayer) {

			//guardar la jugada que lleva a este estado
			_jugada = jugada;

			int nCartasColocadas = 0;

			//setear valores en funcion de isPlayer
			auto& currentDeck = isPlayer ? playerDeck : enemyDeck;
			auto& currentHand = isPlayer ? playerHand : enemyHand;
			auto currentPlayersEnum = isPlayer ? Players::PLAYER1 : Players::PLAYER2;

			//robarCartas
			for (int i = 0; i < jugada.cartasRobadas; i++) {
				Card* c = currentDeck.back();
				currentDeck.pop_back();
				currentHand.push_back(c);
			}

			//poner cartas en el mazo
			for (int i = 0; i < jugada.cartas.size(); i++) {

				//si se coloca la carta
				if (jugada.cartas[i].pos.getX() != -1) {

					int posX = jugada.cartas[i].pos.getX();
					int posY = jugada.cartas[i].pos.getY();

					//poner la carta en el tablero
					_boardBools[posX][posY] = true;
					_boardOwners[posX][posY] = currentPlayersEnum;
					_boardCards[posX][posY] = currentHand[(i - nCartasColocadas)];

					//quitar la carta de la mano
					currentHand.erase(currentHand.begin() + (i - nCartasColocadas));

					//incrementar el numero de cartas colocadas
					nCartasColocadas++;
				}
			}		
		}
	};

	#pragma endregion

	#pragma region Metodos Basicos

	IA_manager();
	~IA_manager();

	void initComponent() override;

	void update() override;

	#pragma endregion

	#pragma region Setters de referencias

	void setMatchManager(MatchManager* matchM);
	void setBoardManager(BoardManager* boardM);

	void setPlayerHand(HandComponent* playerH);
	void setEnemyHand(HandComponent* enemyH);

	void setPlayerDeck(DeckComponent* playerD);
	void setEnemyDeck(DeckComponent* enemyD);

	#pragma endregion


	void StartTurn();
	void RobarCarta();
	void ColocarCarta();


private:

	#pragma region Internal voids

	int heuristic(State* s);

	void posiblesTurnos(
		int cartaActual, int nCartas,
		std::vector<std::vector<CartaColocada>>& soluciones,
		std::vector<CartaColocada>& solAct,
		int puntosRestantes,
		const std::vector<Card*>& playerHand,//mano del jugador, ref const
		std::vector<std::vector<bool>>& _board // true si ocupada, false si libre
	);


	std::vector<InfoJugada> calcularTurno(State s, bool isPlayer);

	std::vector<State> all_posible_next_states(const State& s, bool isPlayer);

	int minimax(int depth, int h, bool isPlayer, State& current_state, State*& best);

	void makePlay(const InfoJugada &play);

#pragma endregion

	#pragma region Referencias externas

	MatchManager* matchManager;
	BoardManager* boardManager;

	HandComponent* playerHandCmp;
	HandComponent* enemyHandCmp;

	DeckComponent* playerDeckCmp;
	DeckComponent* enemyDeckCmp;

	#pragma endregion

	int maxCardInHand = 6;


	// ------ TWEENS ------
	InfoJugada play_;
	bool makePlay_;
	bool colocadas_;
	uint16_t cartasColocadas_;
};






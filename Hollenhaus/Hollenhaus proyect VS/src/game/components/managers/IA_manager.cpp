#include <../pchs/pch.h>

#include "IA_manager.h"

#include "vector"
#include "iostream"
#include <list>

#include "../Card.h"
#include "../../Namespaces.h"
#include <SDL.h>
#include "BoardManager.h"
#include "CardStateManager.h"
#include "MatchManager.h"
#include "../Cell.h"

#include "../DeckComponent.h"
#include "../HandComponent.h"
#include "../DropDetector.h"

//inicializacion de variable estatica del struct State
IA_manager* IA_manager::State::ia_manager = nullptr;


#pragma region Metodos Basicos

IA_manager::IA_manager() :makePlay_(false), colocadas_(false), cartasColocadas_(0) {

	boardManager = nullptr;

	State s;

	s.ia_manager = this;

}

IA_manager::~IA_manager() {}

void IA_manager::initComponent() {}

void IA_manager::update() {
	if (matchManager->getActualState() == Turns::State::IA) {

		// Espera a que haya robado las cartas y se hayan puesto en la mano para colocarlas
		if (enemyHandCmp->doneAnimations() && !colocadas_)
		{
			ColocarCarta();
			colocadas_ = true;
			// Tweens colocar cartas
		}

		// Cuando las cartas son colocadas se pasa de turno
		if (colocadas_)
		{
			matchManager->endTurnIA();
			cartasColocadas_ = 0;
			colocadas_ = false;
		}
	}

}

#pragma endregion

#pragma region Setters de referencias

void IA_manager::setMatchManager(MatchManager* matchM) {
	matchManager = matchM;
}

void IA_manager::setBoardManager(BoardManager* boardM) {
	boardManager = boardM;
}

void IA_manager::setPlayerHand(HandComponent* playerH) {
	playerHandCmp = playerH;
}
void IA_manager::setEnemyHand(HandComponent* enemyH) {
	enemyHandCmp = enemyH;
}

void IA_manager::setPlayerDeck(DeckComponent* playerD) {
	playerDeckCmp = playerD;
}
void IA_manager::setEnemyDeck(DeckComponent* enemyD) {
	enemyDeckCmp = enemyD;
}

#pragma endregion


void IA_manager::StartTurn()
{

	State s;
	s.actionPoints = 4;

	//seteo de los decks
	std::vector<Card*> deckCopyPlayer;
	for (auto c : playerDeckCmp->getDeck()) {
		deckCopyPlayer.push_back(new Card(*c));
	}
	s.playerDeck = deckCopyPlayer;

	std::vector<Card*> deckCopyEnemy;
	for (auto c : enemyDeckCmp->getDeck()) {
		deckCopyEnemy.push_back(new Card(*c));
	}
	s.enemyDeck = deckCopyEnemy;

	//seteo de los hands
	std::vector<Card*> handCopyPlayer;
	for (auto c : playerHandCmp->getHand()) {
		handCopyPlayer.push_back(c);
	}
	s.playerHand = handCopyPlayer;

	std::vector<Card*> handCopyEnemy;
	for (auto c : enemyHandCmp->getHand()) {
		handCopyEnemy.push_back(c);
	}
	s.enemyHand = handCopyEnemy;

	s._boardBools = boardManager->getBoardBoolsIA();
	s._boardCards = boardManager->getBoardCardsIA();
	s._boardOwners = boardManager->getBoardOwnerIA();

	State* best = new State();

	uint32_t time = SDL_GetTicks();

	int value = minimax(0, 1, false, s, best);
	time = SDL_GetTicks() - time;

	//_Tu_Vieja();
#ifdef _DEBUG

	std::cout << std::endl;
	std::cout << "----Resultados minimax---- " << std::endl;
	std::cout << "Time: " << time << std::endl;
	std::cout << "Value: " << value << std::endl;

	//rellenar con info de jugada?
	std::cout << "Jugada:" << std::endl;

	if (best == nullptr) {
		std::cout << "No se ha podido encontrar jugdada" << std::endl;
	}
	else {

		for (int i = 0; i < best->_jugada.cartas.size(); i++) {

			std::cout << "Carta Indice: " << best->_jugada.cartas[i].indice <<
				" Pos: (" << best->_jugada.cartas[i].pos.getX() << "," << best->_jugada.cartas[i].pos.getY() << ")" << std::endl;
		}
	}

	std::cout << "--------------------------" << std::endl;

#endif // _DEBUG


	if (best == nullptr) {

		//seguramente sea pq se queda sin cartas en el mazo
		throw "jugada no encontrada";
	}




	makePlay(best->_jugada);



	for (auto& e : s.playerHand) {
		delete e;
		e = nullptr;
	}

	for (auto& e : s.enemyHand) {
		delete e;
		e = nullptr;
	}

	for (auto& e : s.playerDeck) {
		delete e;
		e = nullptr;
	}

	for (auto& e : s.enemyDeck) {
		delete e;
		e = nullptr;
	}

	for (auto& e : s._boardCards) {
		for (auto& i : e) {
			delete i;
			i = nullptr;
		}
	
	}

	delete best;
}



#pragma region Internal methods 

int IA_manager::heuristic(State* s)
{
	return boardManager->heuristicIA(s);
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
		if (puntosRestantes < 4) {//si hemos consumido algun punto, cambiar magic number
			soluciones.push_back(solAct);
		}
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


std::vector<IA_manager::InfoJugada> IA_manager::calcularTurno(State s, bool isPlayer) {

	std::vector<InfoJugada> allPosiblePlays;

	//NOTA: si cambia el coste del robo hay que cambiar esto

	//la cantidad de veces que se puede robar es el minimo entre los puntos de accion y el tamaño del mazo
	int nRobosPosibles = fmin(s.actionPoints,
		isPlayer ? s.playerDeck.size() : s.enemyDeck.size());

	nRobosPosibles = fmin(nRobosPosibles , (maxCardInHand - (isPlayer ? s.playerHand.size() : s.enemyHand.size())));

	auto& currentDeck = isPlayer ? s.playerDeck : s.enemyDeck;
	auto& currentHand = isPlayer ? s.playerHand : s.enemyHand;

	for (int i = 0; i <= nRobosPosibles; i++)
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

			if (i == 0) {



				bool nula = true;
				//buscar una jugada no nula

				int j = 0;

				while (j < s.size() && nula)
				{
					if (s[j].pos.getX() != 0 || s[j].pos.getY() != 0) {
						nula = false;
						allPosiblePlays.push_back(InfoJugada{ i,s });
					}
					j++;
				}
			}
			else {
				allPosiblePlays.push_back(InfoJugada{ i,s });

			}
		}
	}

	return allPosiblePlays;
}

std::vector<IA_manager::State> IA_manager::all_posible_next_states(const State& s, bool isPlayer) {

	std::vector<State> allStates;

	//dado un estado, aplicamos todas las posible jugadas y generamos todos los posibles futuros estados
	for (auto& jugada : calcularTurno(s, isPlayer)) {
		State nuevo = s;//copia del estado
		nuevo.apply(jugada, isPlayer);//aplicar jugada
		allStates.push_back(nuevo);//añadir a la lista
	}

	return allStates;
}

//current state debería ser const, se ha quitado para evitar crear una copia en la heuristica
//importante no modificar dicha variable
int IA_manager::minimax(int depth, int h, bool isPlayer, State& current_state, State*& best) {

	//si alcanza la profundidad indicada, devuelve el valor de la heurisitca
	if (depth == h) { return current_state.heuristic(); }

	int bestValue = isPlayer ? -99999 : 99999;//cambiar por math min y math max

	for (State& s : all_posible_next_states(current_state, isPlayer)) {

		State* aux = new State(*best);
		
		int current = minimax(depth + 1, h, !isPlayer, s, aux);

		if (isPlayer && current >= bestValue) { //si es jugador, maximiza el valor			
			bestValue = current;
			
			delete best;
			best = new State(s);
		}
		else if (!isPlayer && current <= bestValue) {//si es la IA, lo minimiza
			bestValue = current;

			delete best;
			best = new State(s);
		}

		delete aux;
	}

	return bestValue;
}

void IA_manager::makePlay(const InfoJugada& play)
{
	play_ = play;
	makePlay_ = true;
	cartasColocadas_ = 0;

	RobarCarta();

}

void IA_manager::RobarCarta()
{
	const int draws = play_.cartasRobadas;

	for (int i = 0; i < draws; ++i) {
		// Animacion robar cartas

		enemyHandCmp->addCard(enemyDeckCmp->drawCard()->getEntity());
	}
}

void IA_manager::ColocarCarta()
{
	const std::vector<CartaColocada> cards = play_.cartas;
	cartasColocadas_ = 0;
	//para cada carta
	for (int i = 0; i < cards.size(); i++) {

		Vector2D pos = cards[i].pos;
		//si ponemos la carta
		if (pos != Vector2D(-1, -1)) {
			std::vector<Card*> hand = enemyHandCmp->getHand();
			Card* card = nullptr;
			if (hand.size() > 0) {
				card = hand[i - cartasColocadas_];
			}

			//dropDetector ocupado
			const auto dropDet = boardManager->getCell(pos.getX(), pos.getY())->getEntity()->getComponent<DropDetector>();
			dropDet->setOcuped(true);

			//colocar la carta en el tablero
			// Animacion colocar carta
			if (card != nullptr)
			{
				card->getEntity()->getComponent<Transform>()->setGlobalPos(dropDet->getCardPos());
				card->getEntity()->getComponent<CardStateManager>()->putOnBoard();

				//comunicacion con el boardManager
				const Players::Owner playerTurn = mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>()->getPlayerTurn();
				boardManager->setCard(pos.getX(), pos.getY(), card, playerTurn);

				cartasColocadas_++;
			}

			for (auto& e :hand) {
				delete e;
				e = nullptr;
			}


		}
	}
}
#pragma endregion


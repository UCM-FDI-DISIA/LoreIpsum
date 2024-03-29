#pragma once
#include <list>

// Cantidad de cartas en el juego
const int CARDS_IN_GAME = 50;

class Data
{
private:
	int currentMoney = 0,
		currentCase = 0,
		currentSouls = 0,
		winner = 0;

	// ------ DECKBUILDING -------
	int* drawer; // Id de las cartas desbloqueadas
	std::list<int> maze; // Id de las cartas del mazo 

	// ------ NS ------
	std::list<int> defeatedNPCS;
	int* shopCards; // Guardas las cartas que estan en la tienda en la ronda. Si no hay cartas en (-1 ,-1, -1, -1). Se tiene que actualizar cada ronda.
	bool playerWon; // True si la ultima partida ha sido ganado el jugador. False lo contrario.

	enum WINNER {
		NONE,
		TIE,
		PLAYER1,
		PLAYER2
	};

public:

	//------Constructora y destructora:
	Data();
	Data(int mon, int cas, int sou, std::list<int>maz, int * dra, std::list<int>def);
	~Data();

	//------Setters:
	
	// ------ DECKBUILDING ------
	//----Mazo:
	void AddCardToMaze(int id);
	void SubtractCardFromMaze(int id);
	//----Cajon:
	void AddCardToDrawer(int id);
	void SubtractCardFromDrawer(int id);

	// ------ FLUJO ------
	//----NPCs:
	void AddDefeatedNPC(int id);
	//----Dinero:
	void AddMoney(int m);
	void SubtractMoney(int m);
	//----Almas:
	void AddSouls(int s);
	//----Caso:
	void AddCurrentCase();
	//----Ganardor de la ultima partida:
	void setWinner(int i);
	//----Mete una carta al array de cartas de la tienda. Booleano pues por si acaso.
	bool setShopCard(int id);

	//------Getters:
	
	// ------ DECKBUILDING ------
	//----Mazo:
	const std::list<int> GetMaze() { return maze; }
	//----Cajon:
	int* GetDrawer() { return drawer; }

	// ------ FLUJO ------
	//----NPCs:
	const std::list<int> GetDefeatedNPC(int id) { return defeatedNPCS; }
	//----Dinero:
	const int GetMoney() { return currentMoney; }
	//----Almas:
	const int GetSouls() { return currentSouls; };
	//----Caso:
	const int GetCurrentCase() { return currentCase; };
	//----Ganador de la ultima partida:
	int getWinner() { return winner; }
	//----Comprueba si shopCards esta vacio:
	bool shopCardsIsEmpty();
	//----Devuelve una shopCard dado un id:
	int getShopCardById(int id);

	//------Busqueda:
	
	// ------ DECKBUILDING ------
	//----Mazo:
	bool IdIsInMaze(int id);
	//----Cajon:
	bool IdIsInDrawer(int id);

	// ------ FLUJO ------
	//----NPCs:
	bool IdIsInDefeatedNPC(int id);
	//----Busqueda de una carta de la tienda por id:
	bool IdIsInShopCards(int id);

	//------Escritura:
	void Write();
	//------Lectura:
	void Read();

	//------Vaciar:
	//----Vaciado de todas las listas a la vez.
	void EmptyLists();
	//----Vaciado de la lista del mazo.
	void EmptyMaze();
	//----Vaciado de la lista del cajon.
	void EmptyDrawer();
	//----Vaciado de la lista de NPCs derrotados.
	void EmptyNPCS();
	//----Vaciado del array de cartas de la tienda. Lo pone todo a (-1 ,-1, -1, -1).
	void EmptyShopCards();
};
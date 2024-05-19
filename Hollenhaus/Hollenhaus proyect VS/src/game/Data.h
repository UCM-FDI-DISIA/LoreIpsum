#pragma once

//Checkml
#include <game/checkML.h>

#include <list>
#include <array>

#include <SDL_net.h>



// ---- DECKBUILDING ----
const int CARDS_IN_GAME = 50, // Cantidad de cartas en el juego
MIN_CARDS_MAZE = 10, // Minimo de cartas en el mazo
MAX_CARDS_MAZE = 20, // Maximo de cartas en el mazo
// Cantidad de cartas de la tienda. Cambiar en shopComponent tambien.
CARDS_IN_SHOP = 4;

class RandomNumberGenerator;

class Data
{
private:
	// ---- DECKBUILDING ----
	std::array<int, CARDS_IN_GAME> drawer; // Id de las cartas desbloqueadas
	std::list<int> maze; // Id de las cartas del mazo

	std::vector<int> mazeRival; // Id de las cartas del mazo del rival
	
	std::unordered_map<int, Vector2D> maze_with_pos;

	// ---- MOVIMIENTO ----
	// ultima pos de paul en la ciudad
	Vector2D lastPaulPos;
	bool lastPaulDir = false;

	// ---- FLUJO ----
	int currentMoney = 0,
		currentKeys = 0,
		currentCase = 1,
		currentSouls = 0,
		winner = 0,
		lastState = 0;

	// ---- CONFIGURACION DEL JUEGO ----
	bool automaticNextTurn = true;


	std::list<int> defeatedNPCS;
	int* shopCards; // Guardas las cartas que estan en la tienda en la ronda. Si no hay cartas en (-1 ,-1, -1, -1). Se tiene que actualizar cada ronda.
	bool playerWon; // True si la ultima partida ha sido ganado el jugador. False lo contrario.

	std::list<int> thisCaseClues; // Id de las cartas conseguidas durante el caso (deben ser aniadidas al drawer y aqui al ser conseguidass)

	RandomNumberGenerator& rand_; // Para generar numeros aleatorios.

	enum WINNER {
		NONE,
		TIE,
		PLAYER1,
		PLAYER2
	};

	//MULTIPLAYER
	TCPsocket rival;

	bool isHost = false;

public:

	//------Constructora y destructora:
	Data();
	Data(int mon, int cas, int sou, std::list<int>maz, std::array<int, CARDS_IN_GAME> dra, std::list<int>def);
	~Data();

	// ---- Setters ----
	#pragma region SETTERS
	// -- DECKBUILDING --
	// Mazo:
	void SetNewMaze(std::list<int> newMaze, std::list<Vector2D> mazePos);
	void SetNewMazeRival(std::vector<int> newMaze);
	void SetNewDrawer(std::array<int, CARDS_IN_GAME> newDrawer);
	void SubtractCardFromMaze(int id);
	//----Cajon:
	void AddCardToDrawer(int id);
	void SubtractCardFromDrawer(int id);

	// -- MOVIMIENTO --
	void SetCityPos(Vector2D paulPos);
	void setPaulDir(bool dir) { lastPaulDir = dir;}

	// -- FLUJO --
	// NPCs:
	void AddDefeatedNPC(int id);
	//----Dinero:
	void AddMoney(int m);
	void SubtractMoney(int m);
	//---Leyenda:
	void AddKey();
	//----Almas:
	void AddSouls(int s);
	//----Caso:
	void AddCaseIndex();
	//----Ganardor de la ultima partida:
	void setWinner(int i);
	//----Mete una carta al array de cartas de la tienda. Booleano pues por si acaso.
	bool setShopCard(int id);
	// 
	void setLastState(int ls);

	// ---- CONFIGURACION ----
	void SetAutomaticNextTurn(bool b);


	// ---- Getters ----
	#pragma region GETTERS
	// -- DECKBUILDING --
	// Mazo:
	const std::unordered_map<int, Vector2D> GetMazeWithPos() { return maze_with_pos; }
	const std::list<int> GetMaze() { return maze; }

	const std::vector<int> GetMazeRival() { return mazeRival; }
	// Cajon:
	std::array<int, CARDS_IN_GAME> GetDrawer() { return drawer; }

	// -- MOVIMIENTO --
	Vector2D getLastPaulPos() { return lastPaulPos; }
	bool getLastPaulDir() const { return lastPaulDir; }

	// ------ FLUJO ------
	//----NPCs:
	const std::list<int> GetDefeatedNPC(int id) { return defeatedNPCS; }
	//----Dinero:
	const int GetMoney() { return currentMoney; }
	//----Leyenda:
	int GetKeys() const { return currentKeys; }
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
	//----Devuelve ultimo estado antes de entrar a pausa
	int getLastState() { return lastState; }

	// ---- CONFIGURACION ----
	bool GetAutomaticNextTurn() { return automaticNextTurn; }

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
	void EmptyMaze_With_pos();


	//MULTIPLAYER

	void setSocketRival(TCPsocket _rival);
	TCPsocket getSocketRival();

	void resetSocketRival();

	void setIsHost(bool b);
	bool getIsHost();

	//------Reset:
	void resetSave(); // Copia al save.txt un txt auxiliar (savereset.txt) donde estan los datos para una nueva partida.
};
#pragma once
#include <list>
#include <array>

// ---- DECKBUILDING ----
const int CARDS_IN_GAME = 50, // Cantidad de cartas en el juego
MIN_CARDS_MAZE = 4, // Minimo de cartas en el mazo
MAX_CARDS_MAZE = 6; // Maximo de cartas en el mazo

class Data
{
private:
	// ---- DECKBUILDING ----
	std::array<int, CARDS_IN_GAME> drawer; // Id de las cartas desbloqueadas
	std::list<int> maze; // Id de las cartas del mazo
	
	std::unordered_map<int, Vector2D> maze_with_pos;

	// ---- MOVIMIENTO ----
	// ultima pos de paul en la ciudad
	Vector2D lastPaulPos;

	// ---- FLUJO ----
	int currentMoney = 0,
		currentCase = 0,
		currentSouls = 0,
		winner = 0;

	std::list<int> defeatedNPCS;

	// True si la ultima partida ha sido ganado el jugador
	bool playerWon; 

	enum WINNER {
		NONE,
		TIE,
		PLAYER1,
		PLAYER2
	};

public:
	// ---- Constructoras y destructora ----
	Data();
	Data(int mon, int cas, int sou, std::list<int>maz, std::array<int, CARDS_IN_GAME> dra, std::list<int>def);
	~Data();

	// ---- Setters ----
	#pragma region SETTERS
	// -- DECKBUILDING --
	// Mazo:
	void SetNewMaze(std::list<int> newMaze, std::list<Vector2D> mazePos);
	void SetNewDrawer(std::array<int, CARDS_IN_GAME> newDrawer);
	void SubtractCardFromMaze(int id);

	//Cajon:
	void AddCardToDrawer(int id);
	void SubtractCardFromDrawer(int id);

	// -- MOVIMIENTO --
	void SetCityPos(Vector2D paulPos);

	// -- FLUJO --
	// NPCs:
	void AddDefeatedNPC(int id);

	// Dinero:
	void AddMoney(int m);
	void SubtractMoney(int m);

	// Almas:
	void AddSouls(int s);

	// Caso:
	void AddCurrentCase();

	// Ganador de la ultima partida:
	void setWinner(int i);
	#pragma endregion

	// ---- Getters ----
	#pragma region GETTERS
	// -- DECKBUILDING --
	// Mazo:
	const std::unordered_map<int, Vector2D> GetMaze() { return maze_with_pos; }
	// Cajon:
	std::array<int, CARDS_IN_GAME> GetDrawer() { return drawer; }

	// -- MOVIMIENTO --
	Vector2D getLastPaulPos() { return lastPaulPos; }

	// -- FLUJO --
	// NPCs:
	const std::list<int> GetDefeatedNPC(int id) { return defeatedNPCS; }

	// Dinero:
	const int GetMoney() { return currentMoney; }

	// Almas:
	const int GetSouls() { return currentSouls; };

	// Caso:
	const int GetCurrentCase() { return currentCase; };

	// Ganador de la ultima partida:
	int getWinner() { return winner; }
	#pragma endregion

	// ---- Busqueda ----
	#pragma region BUSQUEDA
	// -- DECKBUILDING --
	// Mazo:
	bool IdIsInMaze(int id);
	// Cajon:
	bool IdIsInDrawer(int id);

	// -- FLUJO --
	// NPCs:
	bool IdIsInDefeatedNPC(int id);
	#pragma endregion

	// ---- Lectura y escritura ----
	void Write();
	void Read();

	// ---- Vaciado ----
	void EmptyLists();
	void EmptyMaze();
	void EmptyDrawer();
	void EmptyNPCS();
	void EmptyMaze_With_pos();
};
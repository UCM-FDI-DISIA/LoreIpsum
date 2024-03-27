#pragma once
#include <list>


class Data
{
private:
	int currentMoney = 0,
		currentCase = 0,
		currentSouls = 0,
		winner = 0;

	// ------ DECKBUILDING -------
	std::vector<int> drawer; // Id de las cartas desbloqueadas
	std::list<int> maze; // Id de las cartas del mazo 

	// ------ NS ------
	std::list<int> defeatedNPCS;
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
	Data(int mon, int cas, int sou, std::list<int>maz, std::vector<int>dra, std::list<int>def);
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

	//------Getters:
	
	// ------ DECKBUILDING ------
	//----Mazo:
	const std::list<int> GetMaze() { return maze; }
	//----Cajon:
	const std::vector<int> GetDrawer() { return drawer; }

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

	//------Busqueda:
	
	// ------ DECKBUILDING ------
	//----Mazo:
	bool IdIsInMaze(int id);
	//----Cajon:
	bool IdIsInDrawer(int id);

	// ------ FLUJO ------
	//----NPCs:
	bool IdIsInDefeatedNPC(int id);

	//------Escritura:
	void Write();
	//------Lectura:
	void Read();

	//------Vaciar:
	void EmptyLists();
	void EmptyMaze();
	void EmptyDrawer();
	void EmptyNPCS();
};
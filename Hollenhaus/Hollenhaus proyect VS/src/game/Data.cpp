#include "pch.h"
#include "Data.h"



//------Constructora y destructora:
Data::Data() : drawer(new int[CARDS_IN_GAME]) { EmptyDrawer(); }
Data::Data(int mon, int cas, int sou, std::list<int>maz, int* dra, std::list<int>def)
	:currentMoney(mon), currentSouls(sou), currentCase(cas), maze(maz), drawer(dra), defeatedNPCS(def)
{};
Data::~Data() {};
//------Setters:

// ------ DECKBUILDING ------
//----Mazo:
void Data::AddCardToMaze(int id) {
	maze.push_back(id);
}
void Data::SubtractCardFromMaze(int id) {
	maze.remove(id);
}
//----Cajon:
void Data::AddCardToDrawer(int id) {
	drawer[id] = id;
}
void Data::SubtractCardFromDrawer(int id) {
	drawer[id] = -1;
}

// ------ FLUJO ------
//----NPCs:
void Data::AddDefeatedNPC(int id) {
	defeatedNPCS.push_back(id);
}
//----Dinero:
void Data::AddMoney(int m) {
	currentMoney += m;
}
void Data::SubtractMoney(int m) {
	currentMoney -= m;
}
//----Almas:
void Data::AddSouls(int s) {
	currentSouls += s;
}
//----Caso:
void Data::AddCurrentCase() {
	currentCase++;
}
//----
void Data::setWinner(int i) {
	winner = WINNER(i);
}

//------Busqueda:

// ------ DECKBUILDING ------
//----Mazo:
bool Data::IdIsInMaze(int id) {
	auto it = std::find(maze.begin(), maze.end(), id);

	return (it != maze.end()) ? true : false;
}
;
//----Cajon:
bool Data::IdIsInDrawer(int id) {
	return drawer[id] == id;
};

// ------ FLUJO ------
//----NPCs:
bool Data::IdIsInDefeatedNPC(int id) {
	auto it = std::find(defeatedNPCS.begin(), defeatedNPCS.end(), id);

	return (it != defeatedNPCS.end()) ? true : false;
};

//------Escribir en el archivo:
void Data::Write() {
	std::ofstream file;
	file.open("resources/saves/save.txt");

	file << currentMoney << "\n";
	file << currentCase << "\n";
	file << currentSouls << "\n";

	file << maze.size() << "\n";
	for (const auto it : maze) {
		file << it << "\n";
	}
	file << CARDS_IN_GAME << "\n";
	for (int i = 0; i < CARDS_IN_GAME; i++) {
		file << drawer[i] << "\n";
	}
	file << defeatedNPCS.size() << "\n";
	for (const auto it : defeatedNPCS) {
		file << it << "\n";
	}
	file.close();
}

//------Lectura del archivo:
void Data::Read() {
	EmptyLists();

	std::ifstream file;
	file.open("resources/saves/save.txt");

	int number, iterations;

	file >> currentMoney >> currentCase >> currentSouls >> iterations;

	for (int i = 0; i < iterations; i++)
	{
		file >> number;
		maze.push_back(number);
	}

	file >> iterations;
	for (int i = 0; i < iterations; i++)
	{
		file >> number;
		drawer[i] = number;
	}

	file >> iterations;
	for (int i = 0; i < iterations; i++)
	{
		file >> number;
		defeatedNPCS.push_back(number);
	}

	file.close();
}

//------Vaciar:
void Data::EmptyLists() {
	EmptyMaze();
	EmptyDrawer();
	EmptyNPCS();
}
void Data::EmptyMaze() {
	maze.clear();
}
void Data::EmptyDrawer() {
	for (int i = 0; i < CARDS_IN_GAME; i++)
	{
		drawer[i] = -1;
	}
}
void Data::EmptyNPCS() {
	defeatedNPCS.clear();
}
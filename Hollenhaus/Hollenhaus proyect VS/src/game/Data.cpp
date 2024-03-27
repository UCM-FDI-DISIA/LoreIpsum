#include "pch.h"
#include "Data.h"

using namespace std;


//------Constructora y destructora:
Data::Data() {}
Data::Data(int mon, int cas, int sou, list<int>maz, list<int>dra, list<int>def)
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
	drawer.push_back(id);
}
void Data::SubtractCardFromDrawer(int id) {
	drawer.remove(id);
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
	auto it = std::find(drawer.begin(), drawer.end(), id);

	return (it != drawer.end()) ? true : false;
};

// ------ FLUJO ------
//----NPCs:
bool Data::IdIsInDefeatedNPC(int id) {
	auto it = std::find(defeatedNPCS.begin(), defeatedNPCS.end(), id);

	return (it != defeatedNPCS.end()) ? true : false;
};

//------Escribir en el archivo:
void Data::Write() {
	ofstream file;
	file.open("resources/saves/save.txt");

	file << currentMoney << "\n";
	file << currentCase << "\n";
	file << currentSouls << "\n";

	file << maze.size() << "\n";
	for (const auto it : maze) {
		file << it << "\n";
	}
	file << drawer.size() << "\n";
	for (const auto it : drawer) {
		file << it << "\n";
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

	ifstream file;
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
		drawer.push_back(number);
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
	drawer.clear();
}
void Data::EmptyNPCS() {
	defeatedNPCS.clear();
}
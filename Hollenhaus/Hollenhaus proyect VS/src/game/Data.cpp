#include "pch.h"
#include "Data.h"

//------Constructora y destructora:
Data::Data() {
	EmptyDrawer();
	//Read();
}

Data::Data(int mon, int cas, int sou, std::list<int>maz, std::array<int, CARDS_IN_GAME> dra, std::list<int>def)
	:currentMoney(mon), currentSouls(sou), currentCase(cas), maze(maz), drawer(dra), defeatedNPCS(def) {};

Data::~Data() {};

//------Setters:
#pragma region SETTERS
// ------ DECKBUILDING ------
//----Mazo:
void Data::SetNewMaze(std::list<int> newMaze) {
	EmptyMaze();
	for (auto e : newMaze)
	{
		maze.push_back(e);
	}
}

void Data::SubtractCardFromMaze(int id) {
	maze.remove(id);
}

//----Cajon:
void Data::AddCardToDrawer(int id) {
	drawer[id] = id;
}

void Data::SetNewDrawer(std::array<int, CARDS_IN_GAME> newDrawer) {

	std::array<int, CARDS_IN_GAME> drawerAux;
	for (int i = 0; i < CARDS_IN_GAME; i++)
	{
		drawerAux[i] = -1;
	}

	for (int i = 0; i < newDrawer.size(); i++)
	{
		if (newDrawer[i] == drawer[i]) {
			drawerAux[i] = newDrawer[i];
		}
	}

	EmptyDrawer();

	for (int i = 0; i < drawerAux.size(); i++)
	{
		drawer[i] = drawerAux[i];
	}


	for (int i = 0; i < newDrawer.size(); i++)
	{
		if (newDrawer[i] != drawer[i]) {
			drawer[i] = newDrawer[i];
		}
	}
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

//----Ganador:
void Data::setWinner(int i) {
	winner = WINNER(i);
}
#pragma endregion

//------Busqueda:
#pragma region BUSQUEDA
// ------ DECKBUILDING ------
//----Mazo:
bool Data::IdIsInMaze(int id) {

	// guarda en el iterador la ubicacion del id en maze
	auto it = std::find(maze.begin(), maze.end(), id);

	// devuelve true la pos es distinta al final
	// (si el it fuese igual al final es que no ha encontrado nada)
	return (it != maze.end()) ? true : false;
}
;
//----Cajon:
bool Data::IdIsInDrawer(int id) {

	// devuelve true si el id de la carta
	// que esta en la pos id es igual al id
	return drawer[id] == id;
};

// ------ FLUJO ------
//----NPCs:
bool Data::IdIsInDefeatedNPC(int id) {

	auto it = std::find(defeatedNPCS.begin(), defeatedNPCS.end(), id);
	return (it != defeatedNPCS.end()) ? true : false;
};
#pragma endregion

//------Escribir y leer el archivo:
#pragma region LECTURA Y ESCRITURA
void Data::Write() {
	std::ofstream file;
	file.open("save.txt");

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
	file.open("save.txt");

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
#pragma endregion

//------Vaciar:
#pragma region VACIADO
void Data::EmptyLists() {
	EmptyMaze();
	EmptyDrawer();
	EmptyNPCS();
}

void Data::EmptyMaze() {

	// se limpia el mazo
	maze.clear();
}

void Data::EmptyDrawer() {

	// recorre todas las cartas del cajon y las pasa a -1
	// (el cajon siempre tiene el tamanio de todas las cartas posibles
	// y los huecos de las cartas que no hayas conseguido segun su id
	// permanecen vacios)
	for (int i = 0; i < CARDS_IN_GAME; i++)
	{
		drawer[i] = -1;
	}
}

void Data::EmptyNPCS() {
	defeatedNPCS.clear();
}
#pragma endregion
#include "pch.h"
#include "Data.h"



//------Constructora y destructora:
Data::Data() : currentMoney(0), currentSouls(0), currentCase(0), shopCards(new int[4] {-1, -1, -1, -1}, drawer(new int[CARDS_IN_GAME]))
{
	EmptyDrawer();
	//Read();
}
Data::Data(int mon, int cas, int sou, std::list<int>maz, std::array<int, CARDS_IN_GAME> dra, std::list<int>def)
	:currentMoney(mon), currentSouls(sou), currentCase(cas), maze(maz), drawer(dra), defeatedNPCS(def), shopCards(new int[4])
{};
Data::~Data() {
	delete shopCards;
};
//------Setters:

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
//----Carta de la tienda:
bool Data::setShopCard(int id) {
	int i = 0;
	bool find = false;
	while (!find && i < 4)
	{
		if (shopCards[i] == -1)
		{
			find = true; // Ha encontrado un hueco.
			shopCards[i] = id; // Guarda la carta en el hueco libre.
		}
		i++;
	}

	if (find) { return true; }
	else { return false; }
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
//----Cartas de la tienda:
bool Data::IdIsInShopCards(int id) {
	int i = 0;
	bool find = false;

	while (!find && i < 4) {
		if (shopCards[i] == id)
		{
			find = true;
		}
		i++;
	}

	return find;
};
//------Getters:
//----Cartas de la tienda:
bool Data::shopCardsIsEmpty() {
	int i = 0;
	bool empty = true; // Suponemos que esta vacio.
	while (empty && i < 4)
	{
		if (shopCards[i] != -1)
		{
			empty = false; // Si hay alguna cartra (no es -1) entonces no esta vacio.
		}
		i++;
	}

	return empty;
}
int Data::getShopCardById(int id) {
	return shopCards[id];
}

//------Escribir en el archivo:
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
	file << 4 << "\n";
	for (int i = 0;i < 4; i++) {
		file << shopCards[i] << "\n";
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

	file >> iterations;
	for (int i = 0; i < iterations; i++)
	{
		file >> number;
		shopCards[i] = number;
	}

	file.close();
}

//------Vaciar:
void Data::EmptyLists() {
	EmptyMaze();
	EmptyDrawer();
	EmptyNPCS();
	EmptyShopCards();
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
void Data::EmptyShopCards() {
	for (int i = 0; i < 4; i++)
	{
		shopCards[i] = -1;
	}
}
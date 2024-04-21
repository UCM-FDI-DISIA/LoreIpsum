#include <../pchs/pch.h>
#include "Data.h"

const std::string SAVE_FILE = "./resources/saves/save.txt";

//------Constructora y destructora:
Data::Data() : currentMoney(1000), currentSouls(0), currentCase(0), shopCards(new int[CARDS_IN_SHOP] {-1, -1, -1, -1})
{
	EmptyDrawer();
	//Read();
}
Data::Data(int mon, int cas, int sou, std::list<int>maz, std::array<int, CARDS_IN_GAME> dra, std::list<int>def)
	:currentMoney(mon), currentSouls(sou), currentCase(cas), maze(maz), drawer(dra), defeatedNPCS(def), shopCards(new int[CARDS_IN_SHOP])
{};
Data::~Data() {
	delete shopCards;
};
//------Setters:

// ------ DECKBUILDING ------
#pragma region DECKBUILDING SETTERS
//----Mazo:
void Data::SetNewMaze(std::list<int> newMaze, std::list<Vector2D> mazePos) {

	// vacia el anterior
	EmptyMaze();
	EmptyMaze_With_pos();
	// guarda iterador al inicio (indice)
	auto itPos = mazePos.begin();

	// recorre el mazo a guardar
	for (auto e : newMaze)
	{
		// aniade la entidad al mazo del data
		maze.push_back(e);

		// busca la entidad en el map mazo de pos
		auto it = maze_with_pos.find(e);

		// si no se encuentra
		if (it == maze_with_pos.end())
		{
			// se inserta id
			it = maze_with_pos.insert({ e,Vector2D() }).first;
		}

		// se guarda la pos en su respectivo id
		(*it).second = (*itPos);

		// se sigue recorriendo (aumenta indice)
		itPos++;
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

	// hacemos array auxiliar 
	std::array<int, CARDS_IN_GAME> drawerAux;

	// lo inicializamos vacio
	for (int i = 0; i < CARDS_IN_GAME; i++)
	{
		drawerAux[i] = -1;
	}

	// recorre el drawer a guardar
	for (int i = 0; i < newDrawer.size(); i++)
	{
		// si la carta ya estaba en el drawer
		if (newDrawer[i] == drawer[i]) {

			// se guarda en el aux en la pos correspondiente a su id
			drawerAux[i] = newDrawer[i];
		}
	}

	// se vacia
	EmptyDrawer();

	// se guardan las cartas que ya estuvieran
	for (int i = 0; i < drawerAux.size(); i++)
	{
		drawer[i] = drawerAux[i];
	}

	// se guardan las cartas nuevas
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
#pragma endregion

// ------ MOVIMIENTO ------
void Data::SetCityPos(Vector2D paulPos)
{
	lastPaulPos = paulPos;
}

// ------ FLUJO ------
#pragma region FLUJO SETTERS
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

void Data::AddKey()
{
	currentKeys++;
}

//----Almas:
void Data::AddSouls(int s) {
	currentSouls += s;
}
//----Caso:
void Data::AddCaseIndex() {
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
	while (!find && i < CARDS_IN_SHOP)
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

void Data::setLastState(int ls)
{
	lastState = ls;
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

	while (!find && i < CARDS_IN_SHOP) {
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
	bool empty = false; // Suponemos que no esta vacio.

	while (!empty && i < CARDS_IN_SHOP)
	{
		if (shopCards[i] == -1)
		{
			empty = true; // Si alguna carta esta en -1 entonces esta vacia.
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
	file.open(SAVE_FILE);

	if (!file.is_open())
	{
#ifdef _DEBUG
		TuVieja("ERROR DE LECTURA: No se ha podido leer el archivo de guardado.");
#endif
		return;
	}

	file << currentMoney << "\n";
	file << currentCase << "\n";
	file << currentSouls << "\n";

	file << "Mazo_y_posiciones" << "\n";
	//Guarda el mazo y posiciones en la pizarra
	file << maze.size() << "\n";
	for (const auto it : maze_with_pos) {
		file << it.first << "\n";
		if (it.first != -1)
		{
			file << it.second.getX() << "\n" << it.second.getY() << "\n";
		}
	}
	file << "Drawer" << "\n";
	//Guarda las cartas desbloqueadas
	file << CARDS_IN_GAME << "\n";
	for (int i = 0; i < CARDS_IN_GAME; i++) {
		file << drawer[i] << "\n";
	}
	//Guarda los npcs derrotados
	file << defeatedNPCS.size() << "\n";
	for (const auto it : defeatedNPCS) {
		file << it << "\n";
	}
	file << CARDS_IN_SHOP << "\n";
	for (int i = 0;i < CARDS_IN_SHOP; i++) {
		file << shopCards[i] << "\n";
	}
	file.close();
}

//------Lectura del archivo:
void Data::Read() {
	EmptyLists();

	std::ifstream file;
	file.open(SAVE_FILE);

	if (!file.is_open())
	{
#ifdef _DEBUG
		TuVieja("ERROR DE ESCRITURA: No se ha podido abrir el archivo de guardado.");
#endif
		return;
	}

	int number, iterations;

	file >> currentMoney >> currentCase >> currentSouls;
	std::string falsedades;
	file >> falsedades;

	//file >> iterations;
	// Lee las posiciones del mazo en la pizarra
	file >> iterations;
	for (int i = 0; i < iterations; i++)
	{
		file >> number;
		maze.push_back(number);

		if (number != -1)
		{
			// lo busco en el map
			auto it = maze_with_pos.find(number);

			// si no esta en el map insertamos la key
			if (it == maze_with_pos.end())
			{
				it = maze_with_pos.insert({ number,Vector2D() }).first;
			}

			// valores x e y de la carta en la pizarra
			int x, y;

			// cojo el valor 
			file >> x >> y;

			// guardamos el valor en la clave
			(*it).second = Vector2D(x, y);
		}
	}

	file >> falsedades;

	// Lee cartas desbloqueadas
	file >> iterations;
	for (int i = 0; i < iterations; i++)
	{
		file >> number;
		drawer[i] = number;
	}

	// Lee los npcs derrotados
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
	for (int i = 0; i < CARDS_IN_SHOP; i++)
	{
		shopCards[i] = -1;
	}
}

void Data::EmptyMaze_With_pos()
{
	maze_with_pos.clear();
}
#pragma endregion

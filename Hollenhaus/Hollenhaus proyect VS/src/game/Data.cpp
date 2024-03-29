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
void Data::SetNewMaze(std::list<int> newMaze, std::list<Vector2D> mazePos) {

	EmptyMaze();
	EmptyMaze_With_pos();

	auto itPos = mazePos.begin();

	for (auto e : newMaze)
	{
		maze.push_back(e);
		auto it = maze_with_pos.find(e);
		if (it == maze_with_pos.end())
		{
			it = maze_with_pos.insert({ e,Vector2D() }).first;
		}

		(*it).second = (*itPos);

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
	file.close();
}

//------Lectura del archivo:
void Data::Read() {
	EmptyLists();

	std::ifstream file;
	file.open("save.txt");

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

void Data::EmptyMaze_With_pos()
{
	maze_with_pos.clear();/*
	for (auto e : maze_with_pos) {
		auto sec = e.second;
		se
	}*/
}
#pragma endregion
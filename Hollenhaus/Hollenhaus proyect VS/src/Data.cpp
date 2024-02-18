#include "Data.h"




//------Constructora y destructora:
Data::Data(int mon, int cas, int sou, list<int>maz, list<int>dra, list<int>def)
	:currentMoney(mon), currentSouls(sou), currentCase(cas), maze(maz), drawer(dra), defeatedNPCS(def)
{};
Data::~Data() {};
//------Setters:
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

//------Busqueda:
//----Mazo:
bool Data::IdIsInMaze(int id) {
	auto it = std::find(maze.begin(), maze.end(), id);

	return (it != maze.end()) ? true : false;

	/*if (it != maze.end()) {
		return true;
	}
	else {
		return false;
	}*/
}
;
//----Cajon:
bool Data::IdIsInDrawer(int id) {
	auto it = std::find(drawer.begin(), drawer.end(), id);

	return (it != drawer.end()) ? true : false;
};
//----NPCs:
bool Data::IdIsInDefeatedNPC(int id) {
	auto it = std::find(defeatedNPCS.begin(), defeatedNPCS.end(), id);

	return (it != defeatedNPCS.end()) ? true : false;
};

//------Escribir en el archivo:
void Data::Write(/*ofstream& fil*/) {
	ofstream file;
	file.open("");

	//file "\n";


	file.close();
}

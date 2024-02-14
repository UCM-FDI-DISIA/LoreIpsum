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

/*//------Getters:
//----Mazo:
void Data::GetMaze();
//----Cajon:
void Data::GetDrawer();
//----NPCs:
void Data::GetDefeatedNPC();
//----Dinero:
int Data::GetMoney() {}
//----Almas:
int Data::GetSouls() {};
//----Caso:
int Data::GetCurrentCase() {};*/

//------Escribir en el archivo:
void Data::Write(/*ofstream& fil*/) {
	ofstream file;
	file.open("");

	//file "\n";


	file.close();
}

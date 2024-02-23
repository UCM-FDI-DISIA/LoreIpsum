#pragma once
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class Data
{
private:
	int currentMoney = 0,
		currentCase = 0,
		currentSouls = 0;
	list<int> maze;
	list<int> drawer;
	list<int> defeatedNPCS;

public:

	//------Constructora y destructora:
	Data();
	Data(int mon, int cas, int sou, list<int>maz, list<int>dra, list<int>def);
	~Data();

	//------Setters:
	//----Mazo:
	void AddCardToMaze(int id);
	void SubtractCardFromMaze(int id);
	//----Cajon:
	void AddCardToDrawer(int id);
	void SubtractCardFromDrawer(int id);
	//----NPCs:
	void AddDefeatedNPC(int id);
	//----Dinero:
	void AddMoney(int m);
	void SubtractMoney(int m);
	//----Almas:
	void AddSouls(int s);
	//----Caso:
	void AddCurrentCase();

	//------Getters:
	//----Mazo:
	const list<int> GetMaze(int id) { return maze; }
	//----Cajon:
	const list<int> GetDrawer(int id) { return drawer; }
	//----NPCs:
	const list<int> GetDefeatedNPC(int id) { return defeatedNPCS; }
	//----Dinero:
	const int GetMoney() { return currentMoney; }
	//----Almas:
	const int GetSouls() { return currentSouls; };
	//----Caso:
	const int GetCurrentCase() { return currentCase; };

	//------Busqueda:
	//----Mazo:
	bool IdIsInMaze(int id);
	//----Cajon:
	bool IdIsInDrawer(int id);
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
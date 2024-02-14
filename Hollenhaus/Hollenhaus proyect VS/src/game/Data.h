#pragma once
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class Data
{
private:

	int currentMoney, currentCase, currentSouls;
	list<int> maze;
	list<int> drawer;
	list<int> defeatedNPCS;

public:

	//------Constructora y destructora:
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
	void GetMaze();
	//----Cajon:
	void GetDrawer();
	//----NPCs:
	void GetDefeatedNPC();
	//----Dinero:
	int GetMoney() { return currentMoney; }
	//----Almas:
	int GetSouls() { return currentSouls; };
	//----Caso:
	int GetCurrentCase() { return currentCase; };
	//------Escritura:
	void Write(/*ofstream& fil*/);
};


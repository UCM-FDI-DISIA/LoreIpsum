#ifndef GameState_H_
#define GameState_H_
#include <array>

/// <summary>
/// Clase GameState (o Manager) vista en clase
/// </summary>
/// 
class Manager;
class Game;
class Data;

class GameState {

protected:

	static Data* data; // puntero a la data

	//LAS ENTIDADES ¡NO! SE CREAN EN LA CONSTRUCTORA SE CREAN EN EL ONENTER Y SE ELIMINAN EN EL ONEXIT 
	GameState() {}; // constructoras de clases abstractas no deberian ser publicas

public:
	virtual ~GameState();		//Destructora

	virtual void refresh(); //borra entidades no vivas
	virtual void update(); //update de las entidades
	virtual void render() const; // render de las entidades

	//Para testeo de estrada y salida de estados
	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	virtual void setWinnerOnData(int w);

	virtual ecs::entity_t createCard(int id, Vector2D pos) { return nullptr; };
	virtual std::array<int, 50> getDrawer();
	virtual std::list<int> getMaze();
	virtual void setMaze(std::list<int> mazeToSave);
	virtual void setDrawer(std::array<int, 50> drawerToSave);
	virtual void saveData();
	virtual void loadData();

	// ---- setters ----
	// settea la data
	static void setData(Data* _data);
};

#endif // !GameState_H_
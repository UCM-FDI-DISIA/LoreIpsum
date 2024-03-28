#ifndef GameState_H_
#define GameState_H_

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


	std::vector<int> getDrawer();

	// ---- setters ----
	// settea la data
	static void setData(Data* _data);
};

#endif // !GameState_H_
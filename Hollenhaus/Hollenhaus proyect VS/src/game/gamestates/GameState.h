#ifndef GameState_H_
#define GameState_H_

//Checkml
#include <game/checkML.h>

#include <array>

#include <SDL_net.h>

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

	//LAS ENTIDADES NO! SE CREAN EN LA CONSTRUCTORA SE CREAN EN EL ONENTER Y SE ELIMINAN EN EL ONEXIT 
	GameState() {}; // constructoras de clases abstractas no deberian ser publicas

public:
	virtual ~GameState();		//Destructora

	virtual void refresh(); //borra entidades no vivas
	virtual void update(); //update de las entidades
	virtual void render() const; // render de las entidades

	//Para testeo de estrada y salida de estados
	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	//virtual void onPause();

	//----Mete una c carta al array de cartas de la tienda de Data.
	virtual void setShopCard(int c);
	//----Comprueba si el array de cartas de la tienda de Data esta vacia.
	virtual bool checkDataShopCardsIsEmpty();
	//----Comprueba si una carta con id id esta en el array de cartas de la tienda de Data.
	virtual bool checkCardIsInDrawer(int id);
	//----Devuelve una carta de shopCards dado un indice.
	virtual int getShopCardById(int id);
	//----Mete una carta con id id al cajon.
	virtual void addCardToDrawer(int id);
	//----Mete dinero al jugador:
	virtual void addMoney(int money);
	//----Mete una llave de la leyenda
	virtual void addKey();
	//----Quita dinero al jugador.
	virtual void substractMoney(int money);
	//----Devuelve el dinero del jugador:
	virtual int getMoney();
	//----Devuelve las almas del jugador:
	virtual int getSouls();
	//----Devuelve el numero de llaves disponibles
	virtual int getKeys();
	//----Comprueba si una carta con id id esta en el mazo.
	virtual bool checkCardIsInMaze(int id);
	//----Devuelve el caso actual.
	virtual int getCurrentCase();
	//----Para ser llamado cuando una carta es seleccionada para que se iluminen las monedas que sean.
	virtual void cardSelected(int prize) {}
	//----Para resetear el brillo de las monedas.
	virtual void deSelected() {}

	virtual void setKey();

	virtual void setJ2(std::string rival);

	virtual void saveData();
	virtual void loadData();

	// ---- crea carta ----
	virtual ecs::entity_t createCard(int id, Vector2D pos);

	// ---- getters ----
	virtual std::array<int, 50> getDrawer();
	virtual std::unordered_map<int, Vector2D> getMazeWithPos();
	virtual std::list<int> getMaze();
	virtual Vector2D getLastPaulPos();
	virtual bool getLastPaulDir() const;
	virtual int GetLastState();
	static Data* getData() { return data; }

	// ---- setters ----
	static void setData(Data* _data); // settea la data
	virtual void setMaze(std::list<int> mazeToSave, std::list<Vector2D> MazePosToSave);
	virtual void setDrawer(std::array<int, 50> drawerToSave);
	virtual void setWinnerOnData(int w);
	virtual void setLastPaulPos(Vector2D paulPos);
	virtual void setLastPaulDir(bool);
	virtual void nextCase();

	//MULTIPLAYER

	virtual void setSocketRival(TCPsocket _rival);
	virtual TCPsocket getSocketRival();

	virtual void resetSocketRival();

	virtual void setIsHost(bool b);
	virtual bool getIsHost();

	virtual void setMazeRival(std::vector<int> mazeRival);
	virtual std::vector<int> getMazeRival();

	virtual void SetLastState(int ls);
};

#endif // !GameState_H_
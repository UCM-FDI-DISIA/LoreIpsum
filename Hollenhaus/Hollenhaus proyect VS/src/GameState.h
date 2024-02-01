#ifndef GameState_H_
#define GameState_H_

#include  "checkML.h"

#include <SDL.h>
#include <iostream>
#include <list>


#include "gameList.h"
#include "GameObject.h"

#include "EventHandler.h"

class Game;

class GameState {

protected:

	Game* game;

	GameList<GameObject, true> gameObjects;

	std::list<EventHandler*> handleEventsObjects;

public:

	GameState(Game* game) :game(game) {};

	virtual ~GameState() {};
	
	virtual void Render() const ;

	virtual void Update();

	virtual void HandleEvent(const SDL_Event& ev);


	void addEventListener(EventHandler* handler);

	void addObject(GameObject* gameObject);

	SDL_Renderer* getRenderer();

};



#endif // !GameState_H_


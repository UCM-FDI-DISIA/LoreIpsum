#ifndef GameStateMachine_H_
#define GameStateMachine_H_

#include "checkML.h"
#include <stack>
#include <functional>
#include "GameState.h"
#include "../utils/Singleton.h"
class Mouse;

namespace ecs
{
	class Manager;
}

class GameStateMachine : public Singleton<GameStateMachine>
{
	std::stack<GameState*> gameStack; // container de los states
	std::list<GameState*> toBeDeleted;

	friend Singleton<GameStateMachine>;

	ecs::Manager* mngr_;
	Mouse* mouse_;

public:
	ecs::Manager* getMngr()
	{
		return mngr_;
	}

	void init();
	//constructor
	GameStateMachine();

	//destructor
	~GameStateMachine() override;


	void pushState(GameState* state); // adds state without removing the previous
	void replaceState(GameState* state); // removes the previous state before adding another
	void popState(); // removes state without adding another

	void Render() const;
	void Update();
	void Refresh();

	bool Empty() const { return gameStack.empty(); }
};


// --------
// forma de usar el singleton Manager
// GameStateMachine::instance()->getMngr()->method() / EN VEZ DE ESTO
// mngr().method() / ESCRIBIR ESTO
inline ecs::Manager& mngr()
{
	return *GameStateMachine::instance()->getMngr();
}
#endif // !GameStateMachine_H_

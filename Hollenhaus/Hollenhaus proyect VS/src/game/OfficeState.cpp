#include "OfficeState.h"
#include "Manager.h"
#include "../sdlutils/InputHandler.h"

OfficeState::OfficeState()
{
	std::cout << "\nLoading Office";
}

void OfficeState::update()
{
}

void OfficeState::render() const
{
}

void OfficeState::refresh()
{
}

void OfficeState::OnLeftClickDown() const
{

}

void OfficeState::onEnter() 
{
	std::cout << "\nEnter office\n";
	for (int i = 0; i < 1000; i++) { TuVieja("Peaches"); }
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().clearState();
	GameStateMachine::instance()->setState(5);
}

void OfficeState::onExit()
{
	std::cout << "\nExit office\n";
}


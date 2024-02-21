#include "CityState.h"
CityState::CityState()
{
	onEnter();
}
void CityState::update()
{
}
void CityState::render() const 
{
}
void CityState::refresh()
{
}


void CityState::onEnter()
{
	std::cout << "entering CityState\n";
}
bool CityState::onExit()
{
	std::cout << "exiting CityState\n";
	return true;
}
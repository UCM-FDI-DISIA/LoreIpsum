#include "CityState.h"
void CityState::update()
{
}
void CityState::render() const 
{
}
void CityState::refresh()
{
}


bool CityState::onEnter()
{
	std::cout << "entering CityState\n";
	return true;
}
bool CityState::onExit()
{
	std::cout << "exiting CityState\n";
	return true;
}
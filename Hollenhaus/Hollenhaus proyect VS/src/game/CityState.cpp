#include "CityState.h"
CityState::CityState()
{
	std::cout << "\nLoading City";
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

void CityState::onEnter() const
{
	std::cout << "\nentering CityState\n";
}

void CityState::onExit() const
{
	std::cout << "\nexiting CityState\n";
}

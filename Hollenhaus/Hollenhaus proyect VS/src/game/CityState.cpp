#include "CityState.h"
const std::string CityState::s_cityID = "CITY";
void CityState::Update()
{
	// nothing for now
}
void CityState::Render()
{
	// nothing for now
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
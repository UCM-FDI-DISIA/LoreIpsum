#include "OfficeState.h"

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

void OfficeState::onEnter() const
{
	std::cout << "\nEnter office\n";
}

void OfficeState::onExit() const
{
	std::cout << "\nExit office\n";
}


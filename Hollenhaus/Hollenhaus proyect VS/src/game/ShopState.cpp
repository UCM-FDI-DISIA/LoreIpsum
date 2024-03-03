#include "ShopState.h"

ShopState::ShopState()
{
	std::cout << "\nLoading Shop";
}

void ShopState::update()
{
}

void ShopState::render() const  
{
}

void ShopState::refresh()
{
}

void ShopState::onEnter()
{
	std::cout << "\nEnter shop\n";
}

void ShopState::onExit() 
{
	std::cout << "\nExit shop\n";
}

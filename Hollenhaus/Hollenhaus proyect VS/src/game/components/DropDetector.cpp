#include "pch.h"
#include "DropDetector.h"
#include "iostream"

DropDetector::DropDetector()
{
	
}

DropDetector::~DropDetector()
{
}

void DropDetector::initComponent()
{
	
}

void DropDetector::update()
{
	
	if (getCardPos() == getBoardPos()) {
		std::cout << "DropDetector::update" << std::endl;
	}
}

#pragma once
#include "Factory.h"
class BoardFactory : public Factory
{
public:
	BoardFactory(int w, int h);

	void createBoard() override;

private:
	int width;
	int heigth;
};


#pragma once
#include "ComponentUpdate.h"

class NPC : public ComponentUpdate
{
public:
	NPC(int id);
	~NPC();
private:
	int _id;
};


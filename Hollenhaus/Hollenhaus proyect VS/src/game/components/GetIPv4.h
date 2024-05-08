#pragma once

//Checkml
#include <game/checkML.h>

#include "ComponentUpdate.h"
#include <string>

// Componente para obtener la IPv4 de tu máquina
class GetIPv4 : public ComponentUpdate
{
public:

	GetIPv4();
	~GetIPv4();

	std::string GetIP() { return ipv4; }
private:

	std::string ipv4;

	std::string ReadIPv4();
};


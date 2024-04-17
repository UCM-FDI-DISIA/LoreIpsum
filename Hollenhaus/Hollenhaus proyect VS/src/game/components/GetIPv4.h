#pragma once
#include "ComponentUpdate.h"
#include <string>

class TextComponent;

class GetIPv4 : public ComponentUpdate
{
public:
	GetIPv4(TextComponent* textComponent);
	~GetIPv4();

	std::string GetIP() { return ipv4; }
private:
	
	TextComponent* tc;

	std::string ipv4;

	std::string ReadIPv4();
};


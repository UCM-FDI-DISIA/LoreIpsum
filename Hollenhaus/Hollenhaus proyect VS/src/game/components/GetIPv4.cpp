#include "pch.h"
#include "GetIPv4.h"
#include <fstream>

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

GetIPv4::GetIPv4(TextComponent* textComponent) :
	tc(textComponent)
{
	ipv4 = ReadIPv4();
}

GetIPv4::~GetIPv4()
{
}

std::string GetIPv4::ReadIPv4()
{
	std::array<char, 10000> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen("C:\\Windows\\System32\\ipconfig", "r"), _pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
		result += buffer.data();
	}

	int i = 0;

	while ((result[i] != 'I' || result[i + 1] != 'P' || result[i + 2] != 'v' || result[i + 3] != '4') && i<9980)
		i++;

	if (result[i] == 'I') i += 4;
	while (!isdigit(result[i]))
		i++;

	std::string IPv4;

	while (isdigit(result[i]) || result[i] == '.') {
		IPv4.push_back(result[i]);
		i++;
	}
		

	std::cout << IPv4;

	return IPv4;
}

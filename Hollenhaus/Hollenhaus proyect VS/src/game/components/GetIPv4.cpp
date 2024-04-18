#include "pch.h"
#include "GetIPv4.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <array>

GetIPv4::GetIPv4()
{
	ipv4 = ReadIPv4();
}

GetIPv4::~GetIPv4()
{
}

std::string GetIPv4::ReadIPv4()
{
	// Primero almacenamos el output de system("C:\\Windows\\System32\\ipconfig") en pipe
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen("C:\\Windows\\System32\\ipconfig", "r"), _pclose);

	std::array<char, 10000> buffer;
	std::string result;
	
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}

	// Trasvasamos el contenido de pipe en un string result
	while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
		result += buffer.data();
	}

	// Buscamos la IPv4 dentro de result. i es nuestro iterador
	int i = 0;

	while ((result[i] != 'I' || result[i + 1] != 'P' || result[i + 2] != 'v' || result[i + 3] != '4') && i<9980)
		i++;

	if (result[i] == 'I') i += 4;
	while (!isdigit(result[i]))
		i++;

	// Almacenamos la IPv4 en otro string, que luego devolvemos
	std::string IPv4;

	while (isdigit(result[i]) || result[i] == '.') {
		IPv4.push_back(result[i]);
		i++;
	}


	return IPv4;
}

#ifndef InvadersError_H_
#define InvadersError_H_

#include "checkML.h"

#include<iostream>
#include <SDL.h>
#include<string>

class InvadersError : public std::logic_error {
	
public:
	//constructor con string
	InvadersError(const std::string& _Message) 
		: logic_error("Error en Space Invaders,  " + _Message) {};

	//constructor con char*
	InvadersError(const char* _Message)
		: logic_error("Error en Space Invaders,  " + std::string(_Message)) {};

	//falta algo mas? , destructores?

};


class SDLError : public InvadersError {

public:
	SDLError() 
		: InvadersError("Error en SDL, " + std::string(SDL_GetError()) ) {};
	SDLError(std::string message)
		:InvadersError(message) {};

};


class FileNotFoundError : public InvadersError {

public:

	FileNotFoundError(const std::string fileName) 
		: InvadersError("FileNotFound, file with name: " + fileName + " , cant be found") {};
	FileNotFoundError(const char* fileName) 
		: InvadersError("FileNotFound, file with name: " + std::string(fileName) + " , cant be found") {};

};


class FileFormatError : public InvadersError{

public:

	FileFormatError(const std::string fileName,int line)
		: InvadersError("FileFormatError, file with name: " + fileName + 
			" , at line: " + std::to_string(line)) {};

	FileFormatError(const char* fileName,int line)
		: InvadersError("FileFormatError, file with name: " + std::string(fileName) + 
			" , at line: " + std::to_string(line)) {};

};
#endif // !InvadersError_H_
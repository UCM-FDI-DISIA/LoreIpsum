#pragma once

//Checkml
#include <game/checkML.h>

#include <string>

class Texture;

class Mouse
{
	Texture* image_;
	SDL_Rect destRect_;
	SDL_Rect srcRect_;

	int frameWidth_;
public:
	Mouse(const std::string&, int);
	~Mouse();
	void render() const;
	void update();
	void changeFrame(int);
};

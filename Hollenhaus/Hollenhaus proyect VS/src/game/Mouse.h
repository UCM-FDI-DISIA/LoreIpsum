#pragma once
#include <SDL_rect.h>
#include <string>

class Texture;

class Mouse
{
	Texture* image_;
	SDL_Rect rect_;

public:
	Mouse(const std::string&);
	~Mouse();
	void render() const;
	void update();
};

#pragma once
#include <SDL_rect.h>
#include <string>

class Texture;

class Mouse
{
	Texture* image_;
	SDL_Rect destRect_;
	SDL_Rect srcRect_;

public:
	Mouse(const std::string&);
	~Mouse();
	void render() const;
	void update();
};

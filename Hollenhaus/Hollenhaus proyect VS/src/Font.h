#ifndef Font_H_
#define Font_H_


#include "checkML.h"


#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include "texture.h"

class Font {
	
	TTF_Font* font = nullptr;

public:
	Font() = default;
	Font(const std::string& filename, int size);
	Font(const Font& font) = delete;
	~Font();

	void load(const std::string& filename, int size);
	void Free();


	SDL_Surface* generateSurface(const std::string& text, SDL_Color color) const;

	Texture* generateTexture(SDL_Renderer* renderer, const std::string& text,
		SDL_Color color) const;
};


#endif // !Font_H_

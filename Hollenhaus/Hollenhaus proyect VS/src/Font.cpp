#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "Font.h"
#include "InvadersError.h"


Font::Font(const std::string& filename, int size) { load(filename, size); }

Font::~Font() { Free(); }

void Font::load(const std::string& filename, int size) {
	font = TTF_OpenFont(filename.c_str(), size);
	//...
}

void Font::Free() {
	TTF_CloseFont(font);
	font = nullptr;
}

SDL_Surface* Font::generateSurface(const std::string& text, SDL_Color color) const {
	return TTF_RenderUTF8_Solid(font, text.c_str(), color);
}

Texture* Font::generateTexture(SDL_Renderer* renderer, const std::string& text,
	SDL_Color color) const 
{
	SDL_Surface* surface = generateSurface(text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr)
		throw SDLError("al crear una textura a partir de texto");

	return new Texture(renderer, texture, 1, 1);
}

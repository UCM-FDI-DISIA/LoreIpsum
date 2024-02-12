// This file is part of the course TPV2@UCM - Samir Genaim

#include "Texture.h"

Texture& Texture::operator=(Texture &&other) noexcept {
	this->~Texture();
	texture_ = other.texture_;
	other.texture_ = nullptr;
	renderer_ = other.renderer_;
	other.renderer_ = nullptr;
	width_ = other.width_;
	height_ = other.height_;

	return *this;
}

Texture::Texture(Texture &&other) noexcept {
	texture_ = other.texture_;
	other.texture_ = nullptr;
	renderer_ = other.renderer_;
	other.renderer_ = nullptr;
	width_ = other.width_;
	height_ = other.height_;
}

Texture::Texture(SDL_Renderer *renderer, const std::string &fileName) {
	assert(renderer != nullptr);
	renderer_ = renderer;

	SDL_Surface *surface = IMG_Load(fileName.c_str());
	if (surface == nullptr)
		throw "Couldn't load image: " + fileName;

	width_ = surface->w;
	height_ = surface->h;

	texture_ = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (texture_ == nullptr)
		throw "Couldn't convert surface to texture for image: " + fileName;
}

Texture::Texture(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color &fgColor) {
	constructFromText(renderer, text, font, &fgColor);
}

Texture::Texture(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color &fgColor, const SDL_Color &bgColor) {
	constructFromText(renderer, text, font, &fgColor, &bgColor);
}

void Texture::constructFromText(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color *fgColor, const SDL_Color *bgColor) {

	assert(renderer != nullptr);
	renderer_ = renderer;

	SDL_Surface *textSurface =
			bgColor == nullptr ?
					font.renderText(text, *fgColor) :
					font.renderText(text, *fgColor, *bgColor);

	if (textSurface == nullptr)
		throw "Couldn't create surface for text: " + text;

	width_ = textSurface->w;
	height_ = textSurface->h;

	texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);

	if (texture_ == nullptr)
		throw "Couldn't create texture for text: " + text;
}

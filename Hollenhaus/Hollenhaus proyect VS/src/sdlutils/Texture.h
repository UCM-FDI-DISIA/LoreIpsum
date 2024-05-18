// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

//Checkml
#include <game/checkML.h>

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cassert>
#include <iostream>
#include "Font.h"

class Texture {
public:

	// cannot copy textures
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	// can be moved
	Texture& operator=(Texture&& other) noexcept;
	Texture(Texture&& other) noexcept;

	// Construct from image
	Texture(SDL_Renderer* renderer, const std::string& fileName);

	// Construct from text
	Texture(SDL_Renderer* renderer, const std::string& text, const Font& font,
		const SDL_Color& fgColor);

	// Construct from text with background
	Texture(SDL_Renderer* renderer, const std::string& text, const Font& font,
		const SDL_Color& fgColor, const SDL_Color& bgColor);

	// Construct from text wrapped
	Texture(SDL_Renderer* renderer, const std::string& text, const Font& font,
		const SDL_Color& fgColor, Uint32 wrapLenght, int align);

	virtual ~Texture() {
		if (texture_ != nullptr)
			SDL_DestroyTexture(texture_); // delete the SDL texture
	}

	inline int width() const {
		return width_;
	}

	inline int height() const {
		return height_;
	}

	// This rendering method corresponds to method SDL_RenderCopyEx.
	//
	// Renders part of the texture (src) to a destination rectangle (dest)
	// with a rotation (angle) around point p (of dest), and flips
	// according to the value of flip. If 'p'is nullptr, the rotation is done
	// wrt. the center
	//
	inline void render(const SDL_Rect& src, const SDL_Rect& dest, double angle,
		const SDL_Point* p = nullptr,
		SDL_RendererFlip flip = SDL_FLIP_NONE) {
		assert(texture_ != nullptr);
		SDL_RenderCopyEx(renderer_, texture_, &src, &dest, angle, p, flip);
	}

	// This rendering method corresponds to method SDL_RenderCopy.
	//
	// Renders part of the texture (src) to a destination rectangle (dest).
	// It can be implemented by calling the previous render method as well,
	// but we use SDL_RenderCopy directly since it does less checks so it
	// saves some checks ...
	inline void render(const SDL_Rect& src, const SDL_Rect& dest) {
		assert(texture_ != nullptr);
		SDL_RenderCopy(renderer_, texture_, &src, &dest);
	}

	// render the complete texture at position (x,y).
	inline void render(int x, int y, int alpha = 255) {
		SDL_Rect dest = { x, y, width_, height_ };
		applyOpacity(alpha);
		render(dest);
	}

	// renders the complete texture at a destination rectangle (dest)
	inline void render(const SDL_Rect& dest, int alpha = 255) {
		SDL_Rect src = { 0, 0, width_, height_ };

		if (alpha != 255)
			applyOpacity(alpha);
		render(src, dest);
	}

	// renders the complete texture at a destination rectangle (dest),
	// with rotation
	inline void render(const SDL_Rect& dest, float rotation) {
		SDL_Rect src = { 0, 0, width_, height_ };
		render(src, dest, rotation);
	}

	/// <summary>
	///  render the complete texture at position (x,y) and anlge (angle)
	/// </summary>
	/// <param name="x">Pos x</param>
	/// <param name="y">Pos y</param>
	/// <param name="mulScaleX">escala x</param>
	/// <param name="mulScaleY">escala y</param>
	/// <param name="angle">Angle</param>
	/// <param name="color">Color a multiplicar</param>
	inline void render(int x, int y, float mulScaleX, float mulScaleY, float angle, 
		SDL_RendererFlip flip = SDL_FLIP_NONE, 
		SDL_Color color = { 255,255,255,0 },
		int alpha = 255)
	{
		SDL_Rect dest = { x, y, width_ * mulScaleX, height_ * mulScaleY };
		SDL_Rect src = { 0, 0, width_, height_ };

		applyOpacity(alpha);

		multiplyColor(color.r, color.g, color.b, color.a);

		render(src, dest, angle, nullptr, flip);
	}

	inline void render(int x, int y, SDL_Rect src, int nRows, int nCols, float mulScaleX, float mulScaleY, float angle, 
		SDL_RendererFlip flip = SDL_FLIP_NONE, 
		SDL_Color color = { 255,255,255,0 },
		int alpha = 255)
	{
		SDL_Rect dest = { x, y, width_ * mulScaleX / nCols, height_ * mulScaleY / nRows };

		applyOpacity(alpha);

		multiplyColor(color.r, color.g, color.b, color.a);

		render(src, dest, angle, nullptr, flip);
	}

	/// <summary>
	/// Multiplica el color pasado por la textura haciendo asi una mezcla
	/// </summary>
	void multiplyColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
	{
		Uint8 a = 255 - alpha;

		//Modulate texture
		SDL_SetTextureColorMod(texture_, red + a, green + a, blue + a);
	}

	/// <summary>
	/// Cambia la opacidad de la textura
	/// </summary>
	void applyOpacity(int alpha = 255)
	{
		SDL_SetTextureAlphaMod(texture_, alpha);
	}

private:

	// Construct from text
	void constructFromText(SDL_Renderer* renderer, const std::string& text,
		const Font& font, const SDL_Color* fgColor,
		const SDL_Color* bgColor = nullptr);

	// Construct from text wrapped
	void constructFromWrappedText(SDL_Renderer* renderer, const std::string& text,
		const Font& font, const SDL_Color* fgColor, Uint32 wrapLenght, int align);

	SDL_Texture* texture_;
	SDL_Renderer* renderer_;
	int width_;
	int height_;
};

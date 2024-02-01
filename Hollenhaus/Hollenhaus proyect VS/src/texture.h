#ifndef TEXTURE_H
#define TEXTURE_H

#include "checkML.h"


#include <SDL.h>
#include <iostream>



/**
 * Object-oriented wrapper for SDL textures with frame support.
 */
class Texture
{
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;

	int width;
	int height;

	size_t nrows;
	size_t ncolumns;

	int frameWidth;
	int frameHeight;

public:
	Texture(SDL_Renderer* renderer, const char* filename, size_t rows = 1, size_t columns = 1);
	Texture(SDL_Renderer* renderer, SDL_Texture* texture, size_t rows = 1, size_t columns = 1);
	~Texture();

	/// Width of a frame in pixels
	int getFrameWidth() const;
	/// Height of a frame in pixels
	int getFrameHeight() const;
	/// Number of frames in each row
	int getNumRows() const;
	/// Number of frames in each column
	int getNumColumns() const;

	/// Render the whole picture filling the entire screen
	void render() const;
	/// Render the whole picture to the given rectangle
	void render(const SDL_Rect& target) const;
	/// Render the whole picture with additional options from SDL_RenderCopyEx
	void render(const SDL_Rect& target,
	            double angle,
	            const SDL_Point* center = nullptr,
	            SDL_RendererFlip flip = SDL_FLIP_NONE) const;

	void render(const SDL_Rect& rect, SDL_Color color) const;

	/// Render a frame to the given rectangle
	void renderFrame(const SDL_Rect& target, int row, int col) const;
	/// Render a frame with additional options from SDL_RenderCopyEx
	void renderFrame(const SDL_Rect& target,
	                 int row,
	                 int col,
	                 double angle,
	                 const SDL_Point* center = nullptr,
	                 SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};

inline int
Texture::getFrameWidth() const
{
	return frameWidth;
}

inline int
Texture::getFrameHeight() const
{
	return frameHeight;
}

inline int
Texture::getNumRows() const
{
	return nrows;
}

inline int
Texture::getNumColumns() const
{
	return ncolumns;
}

#endif // TEXTURE_H

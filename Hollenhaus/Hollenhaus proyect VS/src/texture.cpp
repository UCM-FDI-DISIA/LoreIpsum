#include "checkML.h"


#include "texture.h"

#include <SDL_image.h>



using namespace std;

Texture::Texture(SDL_Renderer* renderer, SDL_Texture* texture, size_t rows, size_t columns)
  : renderer(renderer)
  , texture(texture)
  , nrows(rows)
  , ncolumns(columns)
{
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	frameWidth = width / ncolumns;
	frameHeight = height / nrows;
}

Texture::Texture(SDL_Renderer* renderer, const char* filename, size_t rows, size_t columns)
  : renderer(renderer)
  , texture(nullptr)
  , nrows(rows)
  , ncolumns(columns)
{
	SDL_Surface* surface = IMG_Load(filename);

	if (surface == nullptr)
		throw "load surface \""s + filename + '"';

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	if (texture == nullptr)
		throw "create texture"s;

	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	frameWidth = width / ncolumns;
	frameHeight = height / nrows;
	
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

void
Texture::render() const
{
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

void
Texture::render(const SDL_Rect& rect) const
{
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void
Texture::render(const SDL_Rect& rect,
                double angle,
                const SDL_Point* center,
                SDL_RendererFlip flip) const
{
	SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, center, flip);
}


void
Texture::render(const SDL_Rect& rect, SDL_Color color) const
{
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	render(rect);
	//Restablece el color original de la textura
	SDL_SetTextureColorMod(texture, 255, 255, 255);
}
void
Texture::renderFrame(const SDL_Rect& rect, int row, int col) const
{
	SDL_Rect origin{ col * frameWidth, row * frameHeight, frameWidth, frameHeight };
	SDL_RenderCopy(renderer, texture, &origin, &rect);
}

void
Texture::renderFrame(const SDL_Rect& rect,
                     int row,
                     int col,
                     double angle,
                     const SDL_Point* center,
                     SDL_RendererFlip flip) const
{
	SDL_Rect origin{ col * frameWidth, row * frameHeight, frameWidth, frameHeight };
	SDL_RenderCopyEx(renderer, texture, &origin, &rect, angle, center, flip);
}

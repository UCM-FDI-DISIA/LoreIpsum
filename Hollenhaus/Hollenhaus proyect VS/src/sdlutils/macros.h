// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include <string>
#include "../utils/Vector2D.h"
/*
 * This file includes some SDL related methods/macros, nothing sophisticated, just
 * shortcuts for lengthy instructions
 */


/*
 * build_sdlrect(x,y,w,h)
 *
 * it is used to create a SDL_Rect from the parameters casting them
 * to integer (since we use floating point numbers for dimension,
 * position, velocity, etc.)
 */

inline SDL_Rect build_sdlrect(Vector2D &pos, float w, float h) {
	return
	{
		static_cast<int>(pos.getX()),
		static_cast<int>(pos.getY()),
		static_cast<int>(w),
		static_cast<int>(h)
	};
}

inline SDL_Rect build_sdlrect(float x, float y, float w, float h) {
	return
	{
		static_cast<int>(x),
		static_cast<int>(y),
		static_cast<int>(w),
		static_cast<int>(h)
	};
}

/*
 * COLOR(hexnum)
 *
 * it is used to generate SDL_Color from a hex number (e.g., 0xaaff12ff), so
 * instead of writing
 *
 *  { 0x44, 0x11, 0x22, 0x33 }
 *
 * we simply write build_sdlcolor(0x44112233). It can be provide as a string
 * as well, i.e, build_sdlcolor("0x44112233") which is useful when providing
 * colors in JSON files (JSON does not accept hex)
 */
inline SDL_Color build_sdlcolor(unsigned long num) {
	return
	{
	 static_cast<Uint8>((num >> 24) & 0xff),
	 static_cast<Uint8>((num >> 16) & 0xff),
	 static_cast<Uint8>((num >> 8) & 0xff),
	 static_cast<Uint8>(num & 0xff)
	};
}

inline SDL_Color build_sdlcolor(std::string strnum) {
	return build_sdlcolor(stoul(strnum.erase(0, 2), nullptr, 16));
}

/*
 * COLOREXP(color)
 *
 *  it is  used to expand an SDL_Color into its components, so instead
 *  of writing
 *
 *    SDL_SetRenderDrawColor(game_->getRenderer(), color.r, color.g, color.b, color.a);
 *
 *  we can simply write
 *
 *    SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(color));
 *
 *  or
 *
 *    SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(build_sdlcolor(0x11aa44ff)));
 */
#define COLOREXP(color) \
	color.r, color.g, color.b, color.a



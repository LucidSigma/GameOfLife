#pragma once
#ifndef COLOURS_H
#define COLOURS_H

#include <SDL.h>

namespace Colours
{
	static constexpr SDL_Colour White { 0xFF, 0xFF, 0xFF, 0xFF };
	static constexpr SDL_Colour Blue { 0x00, 0x00, 0xFF, 0xFF };
	static constexpr SDL_Colour Yellow { 0xFF, 0xFF, 0x00, 0xFF };
}

#endif
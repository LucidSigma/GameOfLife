#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

#include <string>

#include "NonCopyable.h"

class Window
	: private NonCopyable
{
private:
	SDL_Window* m_window = nullptr;

public:
	explicit Window() noexcept;
	explicit Window(const std::string& title, const SDL_Rect& rect, unsigned int flags = SDL_WINDOW_SHOWN);

	Window(Window&& other);
	Window& operator =(Window&& other);

	~Window() noexcept;

	inline SDL_Window* GetPointer() const noexcept { return m_window; }
};

#endif
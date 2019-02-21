#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include "NonCopyable.h"

#include <SDL.h>

#include <memory>
#include <string>

class Window
	: private INoncopyable
{
private:
	struct WindowDestroyer
	{
		void operator ()(SDL_Window* window) const noexcept;
	};

	std::unique_ptr<SDL_Window, WindowDestroyer> m_window = nullptr;

public:
	Window() noexcept;
	Window(const std::string& title, const SDL_Rect& rect, unsigned int flags = SDL_WINDOW_SHOWN);

	Window(Window&& other) noexcept;
	Window& operator =(Window&& other) noexcept;

	~Window() noexcept;

	void Destroy() noexcept;

	inline SDL_Window* GetPointer() const noexcept { return m_window.get(); }
};

#endif
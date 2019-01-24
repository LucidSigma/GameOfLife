#include "Window.h"

#include <stdexcept>

Window::Window() noexcept
	: m_window(nullptr)
{ }

Window::Window(const std::string& title, const SDL_Rect& rect, unsigned int flags)
	: m_window(SDL_CreateWindow(title.c_str(), rect.x, rect.y, rect.w, rect.h, flags))
{
	if (m_window == nullptr)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());

		throw std::runtime_error("SDL failed to create window.");
	}
}

Window::Window(Window&& other)
{
	if (m_window != nullptr)
	{
		SDL_DestroyWindow(m_window);
	}

	this->m_window = other.m_window;
	other.m_window = nullptr;
}

Window& Window::operator =(Window&& other)
{
	if (m_window != nullptr)
	{
		SDL_DestroyWindow(m_window);
	}

	this->m_window = other.m_window;
	other.m_window = nullptr;

	return *this;
}

Window::~Window() noexcept
{
	SDL_DestroyWindow(m_window);
}
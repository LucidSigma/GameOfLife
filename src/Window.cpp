#include "Window.h"

#include <stdexcept>
#include <utility>

void Window::WindowDestroyer::operator ()(SDL_Window* window) const noexcept
{
	SDL_DestroyWindow(window);
}

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

Window::Window(Window&& other) noexcept
	: m_window(nullptr)
{
	std::swap(this->m_window, other.m_window);
}

Window& Window::operator =(Window&& other) noexcept
{
	this->m_window = nullptr;
	std::swap(this->m_window, other.m_window);

	return *this;
}

Window::~Window() noexcept
{
	Destroy();
}

void Window::Destroy() noexcept
{
	this->m_window = nullptr;
}
#include "Renderer.h"

#include <stdexcept>

Renderer::Renderer() noexcept
	: m_renderer(nullptr)
{ }

Renderer::Renderer(SDL_Window* window, unsigned int flags, int index)
	: m_renderer(SDL_CreateRenderer(window, index, flags))
{
	if (m_renderer == nullptr)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());

		throw std::runtime_error("SDL failed to create renderer.");
	}
}

Renderer::~Renderer() noexcept
{
	SDL_DestroyRenderer(m_renderer);
}

Renderer::Renderer(Renderer&& other)
{
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
	}

	this->m_renderer = other.m_renderer;
	other.m_renderer = nullptr;
}

Renderer& Renderer::operator =(Renderer&& other)
{
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
	}

	this->m_renderer = other.m_renderer;
	other.m_renderer = nullptr;

	return *this;
}

void Renderer::Draw()
{
	SDL_RenderPresent(m_renderer);
}

void Renderer::DrawRectangle(const SDL_Rect& rect, SDL_Colour colour) noexcept
{
	ChangeColour(colour);
	SDL_RenderFillRect(m_renderer, &rect);
}

void Renderer::DrawLine(SDL_Colour colour, int x1, int y1, int x2, int y2) noexcept
{
	ChangeColour(colour);
	SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
}

void Renderer::Clear(SDL_Colour colour) noexcept
{
	ChangeColour(colour);
	SDL_RenderClear(m_renderer);
}

void Renderer::ChangeColour(SDL_Colour colour) noexcept
{
	SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
}
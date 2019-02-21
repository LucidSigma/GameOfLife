#include "Renderer.h"

#include <stdexcept>
#include <utility>

void Renderer::RendererDestroyer::operator ()(SDL_Renderer* renderer) const noexcept
{
	SDL_DestroyRenderer(renderer);
}

Renderer::Renderer() noexcept
	: m_renderer(nullptr)
{ }

Renderer::Renderer(const Window& window, unsigned int flags, int index)
	: m_renderer(SDL_CreateRenderer(window.GetPointer(), index, flags))
{
	if (m_renderer == nullptr)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());

		throw std::runtime_error("SDL failed to create renderer.");
	}
}

Renderer::Renderer(Renderer&& other) noexcept
	: m_renderer(nullptr)
{
	std::swap(this->m_renderer, other.m_renderer);
}

Renderer& Renderer::operator =(Renderer&& other) noexcept
{
	this->m_renderer = std::exchange(other.m_renderer, nullptr);

	return *this;
}

Renderer::~Renderer() noexcept
{
	Destroy();
}

void Renderer::Draw() const noexcept
{
	SDL_RenderPresent(GetPointer());
}

void Renderer::DrawRectangle(const SDL_Rect& rect, SDL_Colour colour) const noexcept
{
	ChangeColour(colour);
	SDL_RenderFillRect(GetPointer(), &rect);
}

void Renderer::DrawLine(SDL_Colour colour, int x1, int y1, int x2, int y2) const noexcept
{
	ChangeColour(colour);
	SDL_RenderDrawLine(GetPointer(), x1, y1, x2, y2);
}

void Renderer::Clear(SDL_Colour colour) const noexcept
{
	ChangeColour(colour);
	SDL_RenderClear(GetPointer());
}

void Renderer::ChangeColour(SDL_Colour colour) const noexcept
{
	SDL_SetRenderDrawColor(GetPointer(), colour.r, colour.g, colour.b, colour.a);
}

void Renderer::Destroy() noexcept
{
	m_renderer = nullptr;
}
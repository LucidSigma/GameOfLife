#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "NonCopyable.h"

#include "Window.h"

class Renderer
	: private INoncopyable
{
private:
	struct RendererDestroyer
	{
		void operator ()(SDL_Renderer* renderer) const noexcept;
	};

	std::unique_ptr<SDL_Renderer, RendererDestroyer> m_renderer = nullptr;

public:
	Renderer() noexcept;
	Renderer(const Window& window, unsigned int flags, int index = -1);

	Renderer(Renderer&& other) noexcept;
	Renderer& operator =(Renderer&& other) noexcept;

	~Renderer() noexcept;

	void Destroy() noexcept;

	void Draw() const noexcept;
	void DrawRectangle(const SDL_Rect& rect, SDL_Colour colour) const noexcept;
	void DrawLine(SDL_Colour colour, int x1, int y1, int x2, int y2) const noexcept;

	void Clear(SDL_Colour colour) const noexcept;

	inline SDL_Renderer* GetPointer() const noexcept { return m_renderer.get(); }

private:
	void ChangeColour(SDL_Colour colour) const noexcept;
};

#endif
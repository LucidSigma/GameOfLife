#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "NonCopyable.h"

#include "Window.h"

class Renderer
	: private NonCopyable
{
private:
	struct RendererDestroyer
	{
		void operator ()(SDL_Renderer* renderer) const noexcept;
	};

	std::unique_ptr<SDL_Renderer, RendererDestroyer> m_renderer = nullptr;

public:
	explicit Renderer() noexcept;
	explicit Renderer(const Window& window, unsigned int flags, int index = -1);

	Renderer(Renderer&& other) noexcept;
	Renderer& operator =(Renderer&& other) noexcept;

	~Renderer() noexcept;

	void Draw();
	void DrawRectangle(const SDL_Rect& rect, SDL_Colour colour) noexcept;
	void DrawLine(SDL_Colour colour, int x1, int y1, int x2, int y2) noexcept;

	void Clear(SDL_Colour colour) noexcept;

	inline SDL_Renderer* GetPointer() const noexcept { return m_renderer.get(); }

private:
	void ChangeColour(SDL_Colour colour) noexcept;

	void Destroy() noexcept;
};

#endif
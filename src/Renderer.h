#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

#include "NonCopyable.h"

class Renderer
	: private NonCopyable
{
private:
	SDL_Renderer* m_renderer = nullptr;

public:
	explicit Renderer() noexcept;
	explicit Renderer(SDL_Window* window, unsigned int flags, int index = -1);

	Renderer(Renderer&& other);
	Renderer& operator =(Renderer&& other);

	~Renderer() noexcept;

	void Draw();
	void DrawRectangle(const SDL_Rect& rect, SDL_Colour colour) noexcept;
	void DrawLine(SDL_Colour colour, int x1, int y1, int x2, int y2) noexcept;

	void Clear(SDL_Colour colour) noexcept;

	inline SDL_Renderer* GetRenderer() const noexcept { return m_renderer; }

private:
	void ChangeColour(SDL_Colour colour) noexcept;
};

#endif
#pragma once
#ifndef GAME_H
#define GAME_H

#include "CellGrid.h"
#include "Renderer.h"
#include "Window.h"

class Game
{
private:
	static constexpr unsigned int s_FrameRate = 5;

	unsigned int m_windowWidth;
	unsigned int m_windowHeight;

	Window m_window;
	Renderer m_renderer;

	bool m_isRunning = false;
	unsigned int m_ticksCount = 0;

	CellGrid m_cellGrid;

public:
	Game();
	~Game() noexcept;

	void Play();

private:
	bool Initialise() noexcept;

	void PollEvents() noexcept;
	void Update() noexcept;
	void Draw() const noexcept;

	void RegulateFrameRate() noexcept;
};

#endif
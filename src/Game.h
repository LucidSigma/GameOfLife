#pragma once
#ifndef GAME_H
#define GAME_H

#include "CellGrid.h"
#include "Renderer.h"
#include "Window.h"

class Game
{
private:
	static constexpr unsigned int s_WindowWidth = CellGrid::GetCellsPerRow() * CellGrid::GetCellWidth() - 1;
	static constexpr unsigned int s_WindowHeight = CellGrid::GetCellsPerColumn() * CellGrid::GetCellWidth() - 1;

	static constexpr unsigned int s_FrameRate = 5;

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
	bool Initialise();

	void PollEvents();
	void Update();
	void Draw();
};

#endif
#pragma once
#ifndef CELL_GRID_H
#define CELL_GRID_H

#include <string>
#include <vector>

#include "Cell.h"
#include "Renderer.h"

class CellGrid
{
private:
	using CellMatrix = std::vector<std::vector<Cell>>;

	static constexpr unsigned int s_CellWidth = 20;

	unsigned int m_cellsPerRow = 0;
	unsigned int m_cellsPerColumn = 0;

	CellMatrix m_cellGrid;

public:
	constexpr static unsigned int GetCellWidth() noexcept { return s_CellWidth; }

	CellGrid();

	void IterateCells() noexcept;
	void Draw(const Renderer& renderer, unsigned int windowWidth, unsigned int windowHeight) const noexcept;

	inline unsigned int GetCellsPerRow() const noexcept { return m_cellsPerRow; }
	inline unsigned int GetCellsPerColumn() const noexcept { return m_cellsPerColumn; }

private:
	void LoadCellsFromFile(const std::string& filename);

	void DrawGridLines(const Renderer& renderer, unsigned int windowWidth, unsigned int windowHeight) const noexcept;
	void DrawCells(const Renderer& renderer) const noexcept;

	unsigned int GetCellNeighbourCount(unsigned int x, unsigned int y) const noexcept;
};

#endif
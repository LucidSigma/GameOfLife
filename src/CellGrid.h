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
	static constexpr unsigned int s_CellWidth = 20;

	unsigned int m_cellsPerRow = 0;
	unsigned int m_cellsPerColumn = 0;

	std::vector<std::vector<Cell>> m_cellGrid;

public:
	constexpr static unsigned int GetCellWidth() noexcept { return s_CellWidth; }

	CellGrid();

	void IterateCells();
	void Draw(Renderer& renderer, unsigned int windowWidth, unsigned int windowHeight);

	inline unsigned int GetCellsPerRow() noexcept { return m_cellsPerRow; }
	inline unsigned int GetCellsPerColumn() noexcept { return m_cellsPerColumn; }

private:
	void LoadCellsFromFile(const std::string& filename);
	void DrawGridLines(Renderer& renderer, unsigned int windowWidth, unsigned int windowHeight);

	unsigned int GetCellNeighbourCount(unsigned int x, unsigned int y) const;
};

#endif
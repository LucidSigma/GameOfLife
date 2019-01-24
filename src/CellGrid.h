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
	static constexpr unsigned int s_CellsPerRow = 40;
	static constexpr unsigned int s_CellsPerColumn = 40;

	std::vector<std::vector<Cell>> m_cellGrid;

public:
	static constexpr unsigned int GetCellsPerRow() noexcept { return s_CellsPerRow; }
	static constexpr unsigned int GetCellsPerColumn() noexcept { return s_CellsPerColumn; }

	CellGrid();

	void IterateCells();
	void Draw(Renderer& renderer, unsigned int windowWidth, unsigned int windowHeight);

private:
	void LoadCellsFromFile(const std::string& filename);
	void DrawGridLines(Renderer& renderer, unsigned int windowWidth, unsigned int windowHeight);

	unsigned int GetCellNeighbourCount(unsigned int x, unsigned int y) const;
};

#endif
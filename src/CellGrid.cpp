#include "CellGrid.h"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <utility>

#include "Colours.h"

CellGrid::CellGrid()
{
	static const std::string cellFilename = "Cells.txt";
	LoadCellsFromFile(cellFilename);
}

void CellGrid::IterateCells()
{
	std::vector<std::pair<unsigned int, unsigned int>> newCells;
	std::vector<std::pair<unsigned int, unsigned int>> deadCells;

	for (unsigned int i = 0; i < m_cellsPerColumn; i++)
	{
		for (unsigned int j = 0; j < m_cellsPerRow; j++)
		{
			unsigned int neighbourCount = GetCellNeighbourCount(i, j);

			if (m_cellGrid[i][j].IsAlive())
			{
				if (constexpr unsigned int PopulationMin = 2, PopulationMax = 3;
					neighbourCount < PopulationMin || neighbourCount > PopulationMax)
				{
					deadCells.emplace_back(i, j);
				}
			}
			else
			{
				if (constexpr unsigned int RebirthCount = 3;
					neighbourCount == RebirthCount)
				{
					newCells.emplace_back(i, j);
				}
			}
		}
	}

	for (const auto& cell : deadCells)
	{
		m_cellGrid[cell.first][cell.second].SetMortality(false);
	}

	for (const auto& cell : newCells)
	{
		m_cellGrid[cell.first][cell.second].SetMortality(true);
	}
}

void CellGrid::Draw(Renderer& renderer, unsigned int windowWidth, unsigned int windowHeight)
{
	DrawGridLines(renderer, windowWidth, windowHeight);

	for (unsigned int i = 0; i < m_cellGrid.size(); i++)
	{
		for (unsigned int j = 0; j < m_cellGrid[i].size(); j++)
		{
			if (m_cellGrid[i][j].IsAlive())
			{
				SDL_Rect cellRect
				{ 
					static_cast<int>((s_CellWidth - 1) * j + j),
					static_cast<int>((s_CellWidth - 1) * i + i),
					static_cast<int>((s_CellWidth - 1)),
					static_cast<int>((s_CellWidth - 1))
				};
				
				renderer.DrawRectangle(cellRect, Colours::Yellow);
			}
		}
	}
}

void CellGrid::LoadCellsFromFile(const std::string& filename)
{
	std::ifstream cellFile(filename);

	if (!cellFile.is_open())
	{
		throw std::invalid_argument("File " + filename + " could not be opened/found.");
	}

	std::string currentLine;
	unsigned int lineCounter = 0;

	while (std::getline(cellFile, currentLine))
	{
		static constexpr char AliveCell = '*';
		std::vector<Cell> currentRow;

		for (unsigned int i = 0; i < currentLine.length(); i++)
		{
			currentRow.emplace_back(i, lineCounter);

			if (currentLine[i] == AliveCell)
			{
				currentRow.back().SetMortality(true);
			}
		}

		m_cellGrid.push_back(currentRow);
		lineCounter++;
	}

	cellFile.close();

	m_cellsPerRow = m_cellGrid[0].size();
	m_cellsPerColumn = lineCounter;
}

void CellGrid::DrawGridLines(Renderer& renderer, unsigned int windowWidth, unsigned int windowHeight)
{
	for (unsigned int i = s_CellWidth - 1; i < windowWidth; i += s_CellWidth)
	{
		renderer.DrawLine(Colours::White, i, 0, i, windowHeight);
	}

	for (unsigned int i = s_CellWidth - 1; i < windowHeight; i += s_CellWidth)
	{
		renderer.DrawLine(Colours::White, 0, i, windowWidth, i);
	}
}

unsigned int CellGrid::GetCellNeighbourCount(unsigned int x, unsigned int y) const
{
	unsigned int count = 0;

	for (int i = x - 1; i <= static_cast<int>(x + 1); i++)
	{
		for (int j = y - 1; j <= static_cast<int>(y + 1); j++)
		{
			if (i >= 0 && i < static_cast<int>(m_cellGrid.size()) &&
				j >= 0 && j < static_cast<int>(m_cellGrid[i].size()) &&
				!(i == x && j == y) && m_cellGrid[i][j].IsAlive())
			{
				count++;
			}
		}
	}

	return count;
}
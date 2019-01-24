#include "CellGrid.h"

#include <fstream>
#include <stdexcept>
#include <utility>

#include "Colours.h"

CellGrid::CellGrid()
{
	m_cellGrid.reserve(s_CellsPerRow);

	for (unsigned int i = 0; i < s_CellsPerRow; i++)
	{
		std::vector<Cell> currentRow;
		currentRow.reserve(s_CellsPerColumn);

		for (unsigned int j = 0; j < s_CellsPerColumn; j++)
		{
			currentRow.emplace_back(i, j);
		}

		m_cellGrid.push_back(currentRow);
	}

	static const std::string cellFilename = "Cells.txt";
	LoadCellsFromFile(cellFilename);
}

void CellGrid::IterateCells()
{
	std::vector<std::pair<unsigned int, unsigned int>> newCells;
	std::vector<std::pair<unsigned int, unsigned int>> deadCells;

	for (unsigned int i = 0; i < s_CellsPerColumn; i++)
	{
		for (unsigned int j = 0; j < s_CellsPerRow; j++)
		{
			unsigned int neighbourCount = GetCellNeighbourCount(i, j);

			if (m_cellGrid[i][j].IsAlive())
			{
				static constexpr unsigned int PopulationMin = 2;
				static constexpr unsigned int PopulationMax = 3;

				if (neighbourCount < PopulationMin || neighbourCount > PopulationMax)
				{
					deadCells.emplace_back(i, j);
				}
			}
			else
			{
				if (constexpr unsigned int RebirthCount = 3; neighbourCount == RebirthCount)
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
					static_cast<int>((s_CellWidth - 1) * i + i),
					static_cast<int>((s_CellWidth - 1) * j + j),
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

		for (unsigned int i = 0; i < currentLine.length(); i++)
		{
			if (currentLine[i] == AliveCell)
			{
				m_cellGrid[i][lineCounter].SetMortality(true);
			}
		}

		lineCounter++;
	}

	cellFile.close();
}

void CellGrid::DrawGridLines(Renderer& renderer, unsigned int windowWidth, unsigned int windowHeight)
{
	for (unsigned int i = s_CellWidth - 1; i < windowWidth; i += s_CellWidth)
	{
		renderer.DrawLine(Colours::White, i, 0, i, windowWidth);
	}

	for (unsigned int i = s_CellWidth - 1; i < windowHeight; i += s_CellWidth)
	{
		renderer.DrawLine(Colours::White, 0, i, windowHeight, i);
	}
}

unsigned int CellGrid::GetCellNeighbourCount(unsigned int x, unsigned int y) const
{
	unsigned int count = 0;

	for (int i = x - 1; i <= static_cast<int>(x + 1); i++)
	{
		for (int j = y - 1; j <= static_cast<int>(y + 1); j++)
		{
			if ((i >= 0 && i < static_cast<int>(m_cellGrid.size())) && (j >= 0 && j < static_cast<int>(m_cellGrid.size())))
			{
				if (m_cellGrid[i][j].IsAlive() && !(i == x && j == y))
				{
					count++;
				}
			}
		}
	}

	return count;
}
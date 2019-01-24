#pragma once
#ifndef CELL_H
#define CELL_H

class Cell
{
private:
	unsigned int x;
	unsigned int y;

	bool m_isAlive = false;

public:
	explicit Cell(unsigned int x, unsigned int y) noexcept;

	inline void SetMortality(bool mortality) noexcept { m_isAlive = mortality; }
	inline bool IsAlive() const noexcept { return m_isAlive; }
};

#endif
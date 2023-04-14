#ifndef __SUDOKU_SOLVER_H__
#define __SUDOKU_SOLVER_H__

#include <iostream>
#include <iomanip>
#include <initializer_list>

#include "Common/grid.h"
#include "Common/logger.h"

namespace nsCpp_DS {

template<typename T>
class SudokuSolver; // forward declare to make function declaration possible

template<typename T> // declaration
std::ostream& operator<<(std::ostream&, const SudokuSolver<T>&);

// 9 x 9 sudoku solver
template<typename T>
class SudokuSolver
{
	using Grid = ns_Util::Grid<T>;
	using sizeType = typename Grid::sizeType;
public:
	SudokuSolver(std::initializer_list<std::initializer_list<T>> grid)
		:m_grid(grid)
	{}

	inline size_t rows() const { return m_grid.rows(); }
	inline size_t cols() const { return m_grid.cols(); }
		
	inline T& at(sizeType row, sizeType col) { return m_grid.at(row, col); }
	inline const int& at(sizeType row, sizeType col) const { return m_grid.at(row, col); }

	inline T& operator[](sizeType row) { return m_grid[row]; }
	inline const T& operator[](sizeType row) const { return m_grid[row]; }

	inline bool solve() { return solveSudoku(m_grid); }

	friend std::ostream& operator<<(std::ostream& out, const SudokuSolver<T>& obj)
	{
		obj.print(out);
		return out;
	}
protected:
	bool solveSudoku(Grid& grid) const;
	void print(std::ostream& out) const;
private:
	bool findEmptyLocation(const Grid& grid, sizeType& row, sizeType& col) const;
	bool isSafe(const Grid& grid, const sizeType row, const sizeType col, const T& val) const;
	bool usedInRow(const Grid& grid, const sizeType row, const T& val) const;
	bool usedInCol(const Grid& grid, const sizeType col, const T& val) const;
	bool usedIn3x3Box(const Grid& grid, const sizeType row, const sizeType col, const T& val) const;

private:
	Grid		m_grid;
};

template<typename T>
bool SudokuSolver<T>::solveSudoku(Grid& grid) const
{
	sizeType row = 0;
	sizeType col = 0;
	if (!findEmptyLocation(grid, row, col))
	{
		return true;
	}

	for (T i = 1; i < 10; ++i)
	{
		if (isSafe(grid, row, col, i))
		{
			grid[row][col] = i;
			if (solveSudoku(grid))
				return true;
			grid[row][col] = gcBLANK;
		}
	}
	return false;
}

template<typename T>
void SudokuSolver<T>::print(std::ostream& out) const
{
	const size_t setWidth = 2;
	const size_t maxCols = m_grid.cols();
	const size_t maxRows = m_grid.rows();
	for (sizeType i = 0; i < maxRows; ++i)
	{
		if (i && (i % 3u == 0))
		{
			sizeType max = (setWidth + 1) * maxCols + maxCols / 3;
			for (sizeType k = 0; k < max; ++k)
			{
				out << "-";
			}
			out << '\n';
		}

		for (sizeType j = 0; j < maxCols; ++j)
		{
			if (j && (j % 3u == 0))
			{
				out << "| ";
			}
			if (m_grid[i][j] != gcBLANK)
			{
				out << std::setw(setWidth) << m_grid.at(i, j) << " ";
			}
			else
			{
				out << std::setw(setWidth) << char(NULL) << " ";
			}
		}
		out << "\n";
	}
}

template<typename T>
bool SudokuSolver<T>::findEmptyLocation(const Grid& grid, sizeType& row, sizeType& col) const
{
	for (row = 0; row < grid.rows(); ++row)
	{
		for (col = 0; col < grid.cols(); ++col)
		{
			if (grid[row][col] == gcBLANK)
			{
				return true;
			}
		}
	}
	return false;
}

template<typename T>
bool SudokuSolver<T>::isSafe(const Grid& grid, const sizeType row, const sizeType col, const T& val) const
{
	return !usedInRow(grid, row, val) && !usedInCol(grid, col, val) && !usedIn3x3Box(grid, row, col, val);
}

template<typename T>
bool SudokuSolver<T>::usedInRow(const Grid& grid, const sizeType row, const T& val) const
{
	for (sizeType i = 0, size = grid.cols(); i < size; ++i)
	{
		if (grid[row][i] == val)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
bool SudokuSolver<T>::usedInCol(const Grid& grid, const sizeType col, const T& val) const
{
	for (sizeType i = 0, size = grid.rows(); i < size; ++i)
	{
		if (grid[i][col] == val)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
bool SudokuSolver<T>::usedIn3x3Box(const Grid& grid, const sizeType row, const sizeType col, const T& val) const
{
	const sizeType startRow = row - row % 3;
	const sizeType startCol = col - col % 3;

	for (sizeType i = startRow; i < 3 + startRow; ++i)
	{
		for (sizeType j = startCol; j < 3 + startCol; ++j)
		{
			if (grid[i][j] == val)
			{
				return true;
			}
		}
	}
	return false;
}

void test_SudokuSolver_1()
{
	const char* testName = "Sudoku Solve.";
	ns_Util::Logger::LOG_MSG("Executing Test 1 : ", testName, "\n\n");
	SudokuSolver<int> sudo{
		{5, 3, 0,  0, 7, 0,  0, 0, 0},
		{6, 0, 0,  1, 9, 5,  0, 0, 0},
		{0, 9, 8,  0, 0, 0,  0, 6, 0},

		{8, 0, 0,  0, 6, 0,  0, 0, 3},
		{4, 0, 0,  8, 0, 3,  0, 0, 1},
		{7, 0, 0,  0, 2, 0,  0, 0, 6},

		{0, 6, 0,  0, 0, 0,  2, 8, 0},
		{0, 0, 0,  4, 1, 9,  0, 0, 5},
		{0, 0, 0,  0, 8, 0,  0, 7, 9},
	};

	ns_Util::Logger::LOG_MSG("Before Solving\n");
	ns_Util::Logger::LOG_MSG(sudo, '\n');

	sudo.solve();

	ns_Util::Logger::LOG_MSG("After Solving\n");
	ns_Util::Logger::LOG_MSG(sudo, '\n');
}

void test_SudokuSolver()
{
	LOG_ENTRY;
	test_SudokuSolver_1();
	LOG_EXIT;
	ns_Util::Logger::LOG_MSG("#####################################\n");
}
}	// namespace nsCpp_DS
#endif	//#ifndef __SUDOKU_SOLVER_H__
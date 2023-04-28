#pragma once

/*
	8 Queens :	Write an algorithm to print all ways of arranging eight queens on an 8x8 chess board
				so that none of them share the same row, column, or diagonal. In this case, "diagonal"
				means all diagonals, not just the two that bisect the board.
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

const int GRID_SIZE = 8;

class Solution_8_12
{
	bool checkValid(vector<int> &columns, int row1, int col1)
	{
		for (int row2 = 0; row2 < row1; row2++)
		{
			int col2 = columns[row2];

			/*check if rows have a queen in the same column*/
			if (col1 == col2)
			{
				return false;
			}

			/*check diagonals */
			int colDistance = abs(col2 - col1);

			int rowDistance = row1 - row2;

			if (colDistance == rowDistance)
				return false;
		}
		return true;
	}

	void eightQueenUtil(int row, vector<int> columns, vector<vector<int>> &results)
	{
		if (row == GRID_SIZE)	// Found valid placement
		{
			results.push_back(columns);
		}
		else
		{
			for (int col = 0; col < GRID_SIZE; ++col)
			{
				if (checkValid(columns, row, col))
				{
					columns[row] = col;
					eightQueenUtil(row + 1, columns, results);
				}
			}
		}
	}
public:
	void eightQueens()
	{
		vector<int> columns(GRID_SIZE, 0);
		vector<vector<int>> results;
		eightQueenUtil(0, columns, results);

		cout << "Total configurations are : " << results.size() << endl;
	}
};

void test_Ch_8_12()
{
	Solution_8_12 sol;

	sol.eightQueens();
}
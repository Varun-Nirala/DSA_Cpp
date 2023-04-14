#pragma once

/*
	Sorted Matrix Search :	Given an M x N matrix in which each row and column is sorted in ascending order, write
							a method to find an element.
*/


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Coordinate
{
public:
	int row;
	int col;

	Coordinate(int r = -1, int c = -1)
		: row(r)
		, col(c)
	{}

	bool inBounds(const vector<vector<int>> &mat)
	{
		if (mat.empty())
		{
			return row >= 0 && col >= 0 && row < mat.size();
		}
		return row >= 0 && col >= 0 && row < mat.size() && col < mat[0].size();
	}

	bool isBefore(const Coordinate &p)
	{
		return row <= p.row && col <= p.col;
	}

	void setToAverage(const Coordinate &min, const Coordinate &max)
	{
		row = (min.row + max.row) / 2;
		col = (min.col + max.col) / 2;
	}
};

class Solution
{
	Coordinate searchNormal(const vector<vector<int>> &mat, int val)
	{
		Coordinate coord(-1, -1);
		int row = 0;
		int col = mat[0].size() - 1;

		while (row < mat.size() && col >= 0)
		{
			if (mat[row][col] == val)
			{
				coord.row = row;
				coord.col = col;
				break;
			}
			else if (mat[row][col] > val)
			{
				col--;
			}
			else
			{
				row++;
			}
		}
		return coord;
	}

	Coordinate partitionAndSearch(const vector<vector<int>> &mat, Coordinate origin, Coordinate dest, Coordinate pivot, int val)
	{
		Coordinate lowerLeftOrigin(pivot.row, origin.col);
		Coordinate lowerLeftDest(dest.row, pivot.col - 1);

		Coordinate topRightOrigin(origin.row, pivot.col);
		Coordinate topRightDest(pivot.row - 1, dest.col);

		Coordinate coord = findElement(mat, lowerLeftOrigin, lowerLeftDest, val);
		if (!coord.inBounds(mat))
		{
			coord = findElement(mat, topRightOrigin, topRightDest, val);
		}
		return coord;
	}

	Coordinate findElement(const vector<vector<int>> &mat, Coordinate origin, Coordinate dest, int val)
	{
		if (!origin.inBounds(mat) || !dest.inBounds(mat))
			return Coordinate();

		if (mat[origin.row][origin.col] == val)
			return origin;
		else if (!origin.isBefore(dest))
			return Coordinate();

		/*	Set start to start of the diagonal and end to the end of the diagonal. Since the grid may not be square.
		*	the end of the diagonal may not euqal dest
		*/

		int diagDistance = min(dest.row - origin.row, dest.col - origin.col);
		Coordinate start = origin;
		Coordinate end(start.row + diagDistance, start.col + diagDistance);

		Coordinate p(0, 0);

		/*Do binary on the diagonal, looking for first elemetn > val*/
		while (start.isBefore(end))
		{
			p.setToAverage(start, end);
			if (val > mat[p.row][p.col])
			{
				start.row = p.row + 1;
				start.col = p.col + 1;
			}
			else
			{
				end.row = p.row - 1;
				end.col = p.col - 1;
			}
		}

		// split the matrix in quadrants, search the bottom left and top right
		return partitionAndSearch(mat, origin, dest, start, val);
	}

	Coordinate binarySearch(const vector<vector<int>> &mat, int val)
	{
		Coordinate origin(0, 0);
		Coordinate dest(mat.size() - 1, mat[0].size() - 1);
		return findElement(mat, origin, dest, val);
	}

public:
	void find(const vector<vector<int>> &mat, int val, bool useBinarySearch)
	{
		cout << endl;
		if (mat.empty() || mat[0].empty())
		{
			cout << "Empty matrix\n";
			return;
		}
		Coordinate coord;
		cout << "Searching for " << val;
		if (useBinarySearch)
		{
			cout << ", with Binary search\n";
			coord = binarySearch(mat, val);
		}
		else
		{
			cout << ", with Normal search\n";
			coord = searchNormal(mat, val);
		}

		if (coord.row != -1)
		{
			cout << "Found " << " at (" << coord.row << "," << coord.col << ")\n";
		}
		else
		{
			cout << "Not Found!!!\n";
		}
	}
};

int main()
{
	Solution sol;
	vector<vector<int>> mat{
		{15, 20, 40, 85},
		{20, 35, 80, 95},
		{30, 55, 95, 105},
		{40, 80, 100, 120},
	};

	int numToSearch = 55;
	sol.find(mat, numToSearch, true);

	return 0;
}
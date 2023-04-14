#pragma once

/*
	Robot in a Grid :	Imagine a robot sitting on the upper left corner of grid with r rows and c columns.
						The robot can only move in two directions, right and down, but certain cells are "off limits"
						such that the robot cannot step on them. Design an algorithm to find a path for the robot from 
						top left to the bottom right.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <map>

using namespace std;

#define T true
#define F false

typedef struct Point
{
	int r = -1;
	int c = -1;

	Point(int rr, int cc)
		:r(rr)
		, c(cc)
	{}

	friend bool operator<(const Point &lhs, const Point &rhs)
	{
		return lhs.r < rhs.r || (lhs.r == rhs.r && lhs.c < rhs.c);
	}

	friend bool operator==(const Point &lhs, const Point &rhs)
	{
		return lhs.r == rhs.r && lhs.c == rhs.c;
	}
}Point;


class Solution
{
private:
	vector<vector<bool>> m_Grid;

public:
	Solution(vector<vector<bool>> g)
		:m_Grid(g)
	{}

	vector<Point> findPath()
	{
		if (m_Grid.empty() || m_Grid[0].empty())
			return {};

		map<Point, bool> cache;

		int lastRow = m_Grid.size() - 1;
		int lastCol = m_Grid[0].size() - 1;
		vector<Point> path;
		if (pathUtil(lastRow, lastCol, path, cache))
		{
			return path;
		}
		return {};
	}

private:
	bool pathUtil(int row, int col, vector<Point> &path, map<Point, bool> &cache)
	{
		if (row < 0 || col < 0 || !m_Grid[row][col])
			return false;

		Point p(row, col);

		if (cache.count(p))
			return cache[p];

		bool isAtOrigin = (row == 0 && col == 0);
		bool success = false;

		// We can only move up or left [as we staring from bottom]
		if (isAtOrigin || pathUtil(row, col - 1, path, cache) || pathUtil(row - 1, col, path, cache))
		{
			path.push_back(p);
			success = true;
		}
		cache[p] = success;
		return success;
	}
};

int main()
{
	Solution sol({
		{ T, T, T, T, T, T, T, T, T},
		{ F, T, F, T, F, T, F, T, F},
		{ T, T, T, T, T, T, T, T, T},
		{ T, T, T, T, T, T, T, T, T},
		});

	vector<Point> path = sol.findPath();

	for (int i = 0; i < path.size(); ++i)
	{
		cout << path[i].r << "," << path[i].c << endl;
	}

	return 0;
}

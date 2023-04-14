#ifndef __ROTTEN_ORANGES_994_H__
#define __ROTTEN_ORANGES_994_H__

#include <iostream>
#include <vector>

#include "helper.h"

namespace nsCP
{
class Solution994
{
public:
	void test()
	{
		printf("Test : Solution994 -> Rotten Oranges : START\n");
		std::vector<std::vector<std::vector<int>>> qVec;
		qVec.emplace_back(std::vector<std::vector<int>>{ {2, 1, 1}, {1, 1, 0}, {0, 1, 1} });
		qVec.emplace_back(std::vector<std::vector<int>>{ {2, 1, 1}, { 0, 1, 1 }, { 1, 0, 1 } });
		qVec.emplace_back(std::vector<std::vector<int>>{ {0, 2} });

		std::vector<int> aVec{ 4, -1, 0 };

		int failed = 0;
		for (size_t i = 0; i < qVec.size(); ++i)
		{
			print(qVec[i], "Rotten Oranges Grid # " + std::to_string(i + 1));
			if (orangesRotting(qVec[i]) != aVec[i])
			{
				failed++;
			}
		}

		print("Rotten oranges test : ", qVec.size(), failed);
		printf("Test : Solution994 -> Rotten Oranges : END\n\n");
	}

private:
	int orangesRotting(std::vector<std::vector<int>>& grid)
	{
		int ans = 0;
		while (isNewRotten(grid))
		{
			print(grid);
			ans++;
		}

		for (size_t i = 0; i < grid.size(); ++i)
		{
			for (size_t j = 0; j < grid[i].size(); ++j)
			{
				if (grid[i][j] == 1)
					return -1;
			}
		}
		return ans;
	}

	bool isNewRotten(std::vector<std::vector<int>> &grid)
	{
		std::vector<std::vector<int>> vec;

		for (int i = 0; i < grid.size(); ++i)
		{
			for (int j = 0; j < grid[i].size(); ++j)
			{
				if (grid[i][j] == 0 || grid[i][j] == 2)
				{
					continue;
				}
				if (j + 1 < grid[i].size() && grid[i][j + 1] == 2)
				{
					vec.push_back({ i, j });
				}
				else if (i + 1 < grid.size() && grid[i + 1][j] == 2)
				{
					vec.push_back({ i, j });
				}
				else if (j > 0 && i > 0)
				{
					if (grid[i - 1][j] == 2 || grid[i][j - 1] == 2)
					{
						vec.push_back({ i , j });
					}
				}
				else if (i > 0)
				{
					if (grid[i - 1][j] == 2)
					{
						vec.push_back({ i , j });
					}
				}
				else if (j > 0)
				{
					if (grid[i][j - 1] == 2)
					{
						vec.push_back({ i , j });
					}
				}
			}
		}

		if (vec.empty())
			return false;

		for (int i = 0; i < vec.size(); ++i)
		{
			grid[vec[i][0]][vec[i][1]] = 2;
		}

		return true;
	}
};
}
#endif //#ifndef __ROTTEN_ORANGES_994_H__

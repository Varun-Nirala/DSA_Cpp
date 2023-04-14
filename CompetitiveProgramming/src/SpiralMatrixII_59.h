#ifndef __SPIRAL_MATRIX_II_59_H__
#define __SPIRAL_MATRIX_II_59_H__

#include <iostream>
#include <vector>

#include "helper.h"

namespace nsCP
{
class Solution59
{
public:
	void test()
	{
		printf("Test : Solution59 -> Spiral Matrix II : START\n");
		std::vector<int> vec{ 4, 5, 6, 7, 8, 9 };

		std::vector<std::vector<int>> ans;
		for (size_t i = 0; i < vec.size(); ++i)
		{
			ans = generateMatrix(vec[i]);
			print(ans, "Spiral Matrix 2 for n = " + std::to_string(vec[i]));
		}
		printf("Test : Solution59 -> Spiral Matrix II : END\n\n");
	}
private:
	std::vector<std::vector<int>> generateMatrix(int n)
	{
		std::vector<std::vector<int>> ans;
		ans.resize(n);
		for (int i = 0; i < n; ++i)
			ans[i].resize(n);

		int row = 0, col = 0;
		int min = -1, max = n;
		for (int i = 1; i <= n * n;)
		{
			col = row = min + 1;
			while (col < max)
			{
				ans[row][col++] = i++;
			}
			col--;

			row++;
			while (row < max)
			{
				ans[row++][col] = i++;
			}

			row--;
			col--;
			while (col > min)
			{
				ans[row][col--] = i++;
			}

			col++;
			row--;
			while (row > min + 1)
			{
				ans[row--][col] = i++;
			}

			min += 1;
			max -= 1;
		}

		return ans;
	}
};
}
#endif //#ifndef __SPIRAL_MATRIX_II_59_H__
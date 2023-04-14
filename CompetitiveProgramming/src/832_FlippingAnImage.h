#ifndef __832_FLIP_AN_IMAGE_H__
#define __832_FLIP_AN_IMAGE_H__

#include <string>
#include <iostream>
#include <vector>

#include "helper.h"

namespace nsCP
{
class Solution832 {
public:
	void test()
	{
		printf("Test : Solution832 -> Flip an Image : START\n");
		std::vector<std::vector<int>> grid = {
			{1, 1, 0, 0 },
			{1, 0, 0, 1 },
			{0, 1, 1, 1 },
			{1, 0, 1, 0 }};

		print(grid, "Original Matrix : ");
		flipAndInvertImage(grid);
		print(grid, "After flip and invert : ");


		std::vector<std::vector<int>> expectedOutput = {
			{1, 1, 0, 0 },
			{0, 1, 1, 0 },
			{0, 0, 0, 1 },
			{1, 0, 1, 0 } };
		print(expectedOutput, "Expected output : ");
		
		printf("Test : Solution832 -> Flip an Image : END\n\n");
	}
private:
	std::vector<std::vector<int>> flipAndInvertImage(std::vector<std::vector<int>>& A)
	{
		int mid = 0;
		if (A[0].size() % 2 != 0)
		{
			mid = A[0].size() / 2;
		}

		for (int i = 0; i < A.size(); ++i)
		{
			for (int l = 0, r = A[0].size() - 1; l <= r; ++l, --r)
			{
				int val = !A[i][l];
				A[i][l] = !A[i][r];
				A[i][r] = val;
			}
		}

		return A;
	}
};
}
#endif //#ifndef __832_FLIP_AN_IMAGE_H__
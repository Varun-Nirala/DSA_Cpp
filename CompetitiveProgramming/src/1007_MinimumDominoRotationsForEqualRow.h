#ifndef __1007_MIN_DOMINO_ROTATION_H__
#define __1007_MIN_DOMINO_ROTATION_H__

#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

#include "helper.h"

namespace nsCP
{
class Solution1007
{
public:
	void test()
	{
		printf("Test : Solution1007 -> Minimum Dominos Rotation : START\n");
		std::vector<std::vector<int>> vecs;
		vecs.emplace_back(std::vector<int>{ 2, 1, 2, 4, 2, 2 });
		vecs.emplace_back(std::vector<int>{ 5, 2, 6, 2, 3, 2 });

		vecs.emplace_back(std::vector<int>{ 2, 3, 2, 1, 1, 1, 2, 2 });
		vecs.emplace_back(std::vector<int>{ 2, 1, 2, 1, 1, 3, 1, 1 });

		vecs.emplace_back(std::vector<int>{ 1, 2, 1, 1, 1, 2, 2, 2 });
		vecs.emplace_back(std::vector<int>{ 2, 1, 2, 2, 2, 2, 2, 2 });

		for (size_t i = 0; i < vecs.size(); i += 2)
		{
			print(vecs[i], "Vector 1 : ");
			print(vecs[i + 1], "Vector 2 : ");
			std::cout << "Minimum domino rotations : " << minDominoRotations(vecs[i], vecs[i + 1]) << "\n\n";
		}
		printf("Test : Solution1007 -> Minimum Dominos Rotation : END\n\n");
	}

private:
	int minDominoRotations(std::vector<int> &A, std::vector<int> &B)
	{
		int ans = process(A, B);
		if (ans != 0)
		{
			ans = std::min(ans, process(B, A));
		}
		return ans == INT_MAX ? -1 : ans;
	}

	int process(std::vector<int>& A, std::vector<int>& B)
	{
		int ans = INT_MAX;
		if (A.size() != B.size())
			return -1;

		int numOfSwaps = 0;
		for (int i = 0; i < A.size(); ++i)
		{
			numOfSwaps = 0;
			if (i + 1 < A.size() && A[i] == A[i + 1])
			{
				continue;
			}

			for (int j = 0; j < B.size(); ++j)
			{
				if (i != j)
				{
					if (A[i] == B[j] && A[j] != B[j])
					{
						numOfSwaps++;
					}
					else if (A[i] != B[j] && A[i] != A[j])
					{
						numOfSwaps = INT_MAX;
						break;
					}
				}
			}

			if (numOfSwaps < ans)
				ans = numOfSwaps;
		}
		if (ans != INT_MAX && ans + 1 == A.size())
			ans = 0;
		return ans;
	}
};
}
#endif	//#ifndef __1007_MIN_DOMINO_ROTATION_H__

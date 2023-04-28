#pragma once

/*
	Magic Index :	A magic index in an array A[1...n] is defined to be anindex such that A[i] = i.
					Given a sorted array of distinct integers, write a mothod to find that if exist.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <map>

using namespace std;

class Solution_8_3
{
	int magicIndexUtil(const vector<int> &vec, int start, int end)
	{
		if (end < start)
			return -1;

		int mid = (start + end) / 2;
		int midVal = vec[mid];

		if (mid == midVal)
			return mid;

		int leftIndex = min(mid - 1, midVal);
		int left = magicIndexUtil(vec, start, leftIndex);

		if (left >= 0)
			return left;

		int rightIndex = max(mid + 1, midVal);
		int right = magicIndexUtil(vec, rightIndex, end);
		return right;
	}
public:
	int magicIndex(const vector<int> &vec)
	{
		return magicIndexUtil(vec, 0, (int)vec.size() - 1);
	}
};

void test_Ch_8_3()
{
	vector<int> vec({ -10, -5, 2, 2, 2, 3, 4, 7, 9, 12, 13 });
	Solution_8_3 sol;

	cout << sol.magicIndex(vec) << endl;
}
#pragma once

/*
	Sorted Merge :	You are given two sorted arrays, A and B, where A has large enough buffer at the end to hold B.
					Write a method to merge B into A in sorted order.
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Solution_10_1
{
public:
	bool mergeSorted(vector<int> &vecA, int sizeA, const vector<int> &vecB, int sizeB)
	{
		if (vecA.size() != sizeA + sizeB)
		{
			return false;
		}

		int idA = sizeA - 1;
		int idB = sizeB - 1;
		int idMerge = sizeA + sizeA - 1;

		while (idB >= 0)
		{
			if (idA >= 0 && vecA[idA] > vecB[idB])
			{
				vecA[idMerge] = vecA[idA];
				idA--;
			}
			else
			{
				vecA[idMerge] = vecB[idB];
				idB--;
			}
			idMerge--;
		}
		return true;
	}
};

void test_Ch_10_1()
{
	Solution_10_1 sol;
	vector<int> vecA = { 1, 3, 5, 7, 8, 9, 10 };
	int sizeA = (int)vecA.size();

	vector<int> vecB = { 2, 4, 6, 11, 12, 13, 14 };
	int sizeB = (int)vecB.size();

	vecA.resize(vecA.size() + vecB.size());

	sol.mergeSorted(vecA, sizeA, vecB, sizeB);

	for (auto x : vecA)
	{
		cout << x << " ";
	}
	cout << endl;
}
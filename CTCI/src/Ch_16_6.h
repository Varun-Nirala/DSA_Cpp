#pragma once

/*
	Smallest Difference :	Given two arrays of integers. Compute the pair of values (one value in each array) 
							with the smallest (non-negative) difference. Return the difference.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution
{
public:
	int smallestDifference(vector<int> vecA, vector<int> vecB)
	{
		sort(vecA.begin(), vecA.end());
		sort(vecB.begin(), vecB.end());

		int difference = INT_MAX;
		int a = 0;
		int b = 0;

		while (a < vecA.size() && b < vecB.size())
		{
			int currDiff = abs(vecA[a] - vecB[b]);
			if (currDiff < difference)
				difference = currDiff;

			if (vecA[a] < vecB[b])
				a++;
			else
				b++;
		}
		return difference;
	}
};

int main()
{
	vector<int> vecA = { 1, 3, 15, 11, 2 };
	vector<int> vecB = { 23, 127, 235, 19, 8 };
	Solution sol;
	return 0;
}
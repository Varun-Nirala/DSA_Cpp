#pragma once

/*
	Peaks and Valleys :	In an array of integers, a "peak" is an element which is >= to the adjacent integers
						and a "valley" is an element which is <= the adjacent integers.
						For example, in the array (5, 8, 6, 2, 3, 4, 6), (8, 6) are peaks and (2, 3) are valleys.
						Given an array of integers, sort the array into an alternating sequence of peaks and valleys.

						Example :
						Input	: (5, 3, 1, 2, 3)
						Ouput	: (5, 1, 3, 2, 3)
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "common.h"

using namespace std;

class Solution_10_11
{
public:
	void rearrangeInPeakAndValleyWithSorting(vector<int> &vec)
	{
		cout << "Called : " << __FUNCTION__ << endl;
		sort(vec.begin(), vec.end(), less<int>());
		PrintArray(vec, std::string("Printing Sorted Array : "));

		for (int i = 1; i < vec.size(); i += 2)
		{
			swap(vec[i - 1], vec[i]);
			//PrintArray(vec, "Printing Array Pass " + to_string(i) + " : ");
		}
	}

	void rearrangeInPeakAndValleyWithoutSorting(vector<int> &vec)
	{
		cout << "Called : " << __FUNCTION__ << endl;
		for (int i = 1; i < vec.size(); i += 2)
		{
			int biggestIndex = maxIndex(vec, i);
			if (i != biggestIndex)
			{
				swap(vec[i], vec[biggestIndex]);
			}
		}
	}
private:
	int maxIndex(const vector<int> &vec, int b)
	{
		int a = b - 1;
		int c = b + 1;
		int size = (int)vec.size();

		int aValue = (a >= 0 && a < size) ? vec[a] : INT_MIN;
		int bValue = (b >= 0 && b < size) ? vec[b] : INT_MIN;
		int cValue = (c >= 0 && c < size) ? vec[c] : INT_MIN;

		int maxVal = max(aValue, max(bValue, cValue));

		if (maxVal == aValue)
		{
			return a;
		}
		else if (maxVal == bValue)
		{
			return b;
		}
		return c;
	}
};

void test_Ch_10_11()
{
	vector<int> vec{ 9, 8, 4, 0, 1, 7 };
	Solution_10_11 sol;

	PrintArray(vec, std::string("Printing Original Array : "));
	sol.rearrangeInPeakAndValleyWithSorting(vec);
	PrintArray(vec, std::string("\n\nPrinting Re-arranged Array : "));


	vector<int> vec1{ 9, 8, 4, 0, 1, 7 };
	PrintArray(vec1, std::string("\n\nPrinting Original Array : "));
	sol.rearrangeInPeakAndValleyWithSorting(vec1);
	PrintArray(vec1, std::string("\n\nPrinting Re-arranged Array : "));
}
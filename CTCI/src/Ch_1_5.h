#pragma once

/*
	One-Way :	There are types of edits that can be perfomed.
				1. Insert a char
				2. Remove a char
				3. Replace a char
				Check if two strings are one(or zero) edit away
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution_1_5
{
public:
	bool oneAway(string &strA, string &strB)
	{
		int aSize = (int)strA.size();
		int bSize = (int)strB.size();
		if (aSize - bSize > 1 || aSize - bSize < -1)
			return false;

		int numOfEdit = 0;
		if (aSize == bSize)
		{
			for (int i = 0; i < aSize; ++i)
			{
				if (strA[i] != strB[i])
				{
					numOfEdit++;
					if (numOfEdit > 1)
					{
						return false;
					}
				}
			}
		}
		else
		{
			string &minStr = aSize > bSize ? strB : strA;
			string &maxStr = aSize < bSize ? strB : strA;

			if (aSize > bSize)
				swap(aSize, bSize);

			numOfEdit = 0;
			for (int i = 0, j = 0; i < aSize; ++i, ++j)
			{
				if (minStr[i] != maxStr[j])
				{
					i++;
					numOfEdit += 1;
					if (numOfEdit > 1)
						return false;
				}
			}
		}
		return true;
	}
};

void test_Ch_1_5()
{
	Solution_1_5 sol;

	vector<string> vecA{ "pale", "pales", "pale", "pale" };
	vector<string> vecB{ "ple", "pale", "bale", "bake" };
	vector<bool> ans{ true, true, true, false };

	for (int i = 0; i < 4; ++i)
	{
		if (sol.oneAway(vecA[i], vecB[i]) == ans[i])
		{
			cout << "PASS :: " << boolalpha << ans[i] << "\t" << vecA[i] << " -> " << vecB[i] << endl;
		}
		else
		{
			cout << "FAIL :: " << boolalpha << ans[i] << "\t" << vecA[i] << " -> " << vecB[i] << endl;
		}
	}
}
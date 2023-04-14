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

class Solution
{
public:
	bool oneAway(string &strA, string &strB)
	{
		int aSize = strA.size();
		int bSize = strB.size();
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

			int numOfEdits = 0;
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

int main()
{
	Solution sol;

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
	return 0;
}
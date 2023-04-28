#pragma once

/*
	Check Permutation : Check if one string is permutation of other
*/

#include <iostream>
#include <string>

using namespace std;

class Solution_1_2
{
public:
	bool checkPermutation(string &strA, string &strB)
	{
		if (strA.size() != strB.size())
			return false;

		int freq[256] = { 0 };

		for (int i = 0; i < strA.size(); ++i)
		{
			freq[strA[i]] += 1;
			freq[strB[i]] -= 1;
		}

		for (int i = 0; i < 256; ++i)
		{
			if (freq[i] != 0)
				return false;
		}

		return true;
	}
};

void test_Ch_1_2()
{
	string strA("abcb");
	string strB("bcaa");
	Solution_1_2 sol;

	cout << boolalpha << sol.checkPermutation(strA, strB) << endl;
}

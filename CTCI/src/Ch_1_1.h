#pragma once
/*
	Is Unique :	Implement an algorithm to determine if a string has all characters.
				What if you cannot use additional DS.
*/
#include <iostream>
#include <string>

using namespace std;

class Solution_1_1
{
	public:
		bool isUnique(string &str)
		{
			if (str.size() > 128)
				return false;

			bool freq[128] = { false };

			for (auto x : str)
			{
				if (freq[x])
					return false;
				freq[x] = true;
			}
			return true;
		}
};

void test_Ch_1_1()
{
	string str("abcab");
	Solution_1_1 sol;

	cout << boolalpha << sol.isUnique(str) << endl;
}
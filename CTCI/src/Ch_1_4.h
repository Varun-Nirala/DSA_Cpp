#pragma once

/*
	Palindrome Permutation :		Check if a string is a permutation of palindrome		
*/

#include <iostream>
#include <string>

using namespace std;

class Solution_1_4
{
private:
	bool isPalindrome(const string &str)
	{
		int lt = 0;
		int rt = (int)str.size() - 1;

		while (lt < rt)
		{
			if (str[lt] != str[rt])
			{
				return false;
			}
			lt++;
			rt--;
		}
		return true;
	}

public:
	bool checkIsAnyPermutationPalindrome(string &str)
	{
		int freq[256] = { 0 };

		for (auto x : str)
		{
			if (x != ' ')
			{
				if (x >= 'A' && x <= 'Z')
				{
					x = 'a' + x - 'A';
				}
				freq[x] += 1;
			}
		}

		bool onlyOne = false;
		for (int i = 0; i < 256; ++i)
		{
			if (freq[i] % 2 == 0)
			{
				;
			}
			else if (freq[i] > 0)
			{
				if (!onlyOne)
				{
					onlyOne = true;
				}
				else
				{
					return false;
				}
			}
		}
		return true;
	}
};

void test_Ch_1_4()
{
	Solution_1_4 sol;
	string str("Tact Coa");
	cout << boolalpha << sol.checkIsAnyPermutationPalindrome(str) << endl;

	for (int i = 0; i < 26; ++i)
	{
		cout << (1 << i) << endl;
	}
}

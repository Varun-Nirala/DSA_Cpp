#pragma once
/*
	URLify :		Write a method to replace all spaces in a string with '%20'.
				You may assume that the string has sufficient space at the end to hold the
				additional characters, and that you are given the "true" length of the string.
*/

#include <iostream>
#include <string>

using namespace std;

class Solution_1_3
{
public:
	void URLify(string &str, int trueLength)		// trueLenth is length after trimming of end spaces
	{
		int rt = (int)str.size();

		if (rt == trueLength)
			return;

		rt -= 1;
		int lt = trueLength - 1;

		int numOfSpaces = 0;
		for (int i = 0; i < trueLength; ++i)
		{
			if (str[i] == ' ')
				numOfSpaces++;
		}

		// To take care of scenario where more than required space is there at end START
		rt = lt + (numOfSpaces * 2);
		if (rt + 1 < str.size())
		{
			str[rt + 1] = '\0';
		}
		// To take care of scenario where more than required space is there at end END

		while (lt >= 0)
		{
			if (str[lt] != ' ')
			{
				str[rt--] = str[lt];
			}
			else
			{
				str[rt--] = '0';
				str[rt--] = '2';
				str[rt--] = '%';
			}
			lt--;
		}
	}
};

void test_Ch_1_3()
{
	string str("Mr John Smith      ");
	//string str("Mr%20John%20Smith");
	Solution_1_3 sol;

	sol.URLify(str, 13);
	cout << str << endl;
}
#ifndef __1221_SPLIT_A_STRING_IN_BALANCED_STRING_H__
#define __1221_SPLIT_A_STRING_IN_BALANCED_STRING_H__

#include <iostream>
#include <string>
#include <vector>

#include "helper.h"

/*
1221. Split a String in Balanced Strings

Balanced strings are those who have equal quantity of 'L' and 'R' characters.
Given a balanced string s split it in the maximum amount of balanced strings.
Return the maximum amount of splitted balanced strings.

Example 1:
	Input: s = "RLRRLLRLRL"
	Output : 4
	Explanation : s can be split into "RL", "RRLL", "RL", "RL", each substring contains same number of 'L' and 'R'.

Example 2 :
	Input : s = "RLLLLRRRLR"
	Output : 3
	Explanation : s can be split into "RL", "LLLRRR", "LR", each substring contains same number of 'L' and 'R'.

Example 3 :
	Input : s = "LLLLRRRR"
	Output : 1
	Explanation : s can be split into "LLLLRRRR".

Example 4 :
	Input : s = "RLRRRLLRLL"
	Output : 2
	Explanation : s can be split into "RL", "RRRLLRLL", since each substring contains an equal number of 'L' and 'R'

Constraints :
	1 <= s.length <= 1000
	s[i] = 'L' or 'R'
*/


namespace nsCP
{
class Solution1221
{
public:
	void test()
	{
		printf("Test : Solution1221 -> Split a string in balanced strings : START\n");
		std::vector<std::string> input = { "RLRRLLRLRL", "RLLLLRRRLR", "LLLLRRRR", "RLRRRLLRLL", "RRLRRLRLLLRL" };
		std::vector<int> output = { 4, 3, 1, 2, 2 };

		int failed = 0;
		for (size_t i = 0; i < input.size(); ++i)
		{
			std::cout << "Input String : " << input[i];
			int ans = balancedStringSplit(input[i]);
			std::cout << ", output = " << ans << " , expected = " << output[i] << '\n';
			
			if (ans != output[i])
			{
				failed++;
			}
		}
		print("Balanced string split.", input.size(), failed);
		printf("Test : Solution1221 -> Split a string in balanced strings : END\n\n");
	}
private:
	int balancedStringSplit(std::string s)
	{
		int r = 0, l = 0, count = 0;
		for (int i = 0; i < s.length(); i++) {
			if (s.at(i) == 'L')
				l++;
			if (s.at(i) == 'R')
				r++;
			if (l == r)
				count++;
		}
		return count;
	}
};
}
#endif //#ifndef __1221_SPLIT_A_STRING_IN_BALANCED_STRING_H__
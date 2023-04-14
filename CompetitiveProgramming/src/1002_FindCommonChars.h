#ifndef __1002_FIND_COMMON_CHARS_H__
#define __1002_FIND_COMMON_CHARS_H__

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "helper.h"

namespace nsCP
{
/*
Given an array A of strings made only from lowercase letters, return a list of all characters that show up in all strings within the list(including duplicates).
For example, if a character occurs 3 times in all strings but not 4 times, you need to include that character three times in the final answer.

You may return the answer in any order.

Example 1:
	Input: ["bella", "label", "roller"]
	Output : ["e", "l", "l"]

Example 2 :
	Input : ["cool", "lock", "cook"]
	Output : ["c", "o"]

Note :
	1 <= A.length <= 100
	1 <= A[i].length <= 100
	A[i][j] is a lowercase letter
*/
class Solution1002 {
	void test()
	{
		printf("Test : Solution1002 -> Find Common Chars : START\n");
		std::cout << "Test Common chars : \n\n";
		std::vector<std::string> inp1 = { "bella", "label", "roller" };
		std::vector<std::string> inp2 = { "cool", "lock", "cook" };

		print(inp1, "Vector 1 :");
		std::vector<std::string> vec1 = commonChars(inp1);
		print(vec1);

		print(inp2, "Vector 2 :");
		vec1 = commonChars(inp2);

		print(inp2, "Output vector with common chars :");
		printf("Test : Solution1002 -> Find Common Chars : END\n\n");
	}

private:
	std::vector<std::string> commonChars(std::vector<std::string>& A)
	{
		std::vector<std::vector<int>> table;

		// row is char and column
		table.resize(26);
		for (int i = 0; i < 26; ++i)
		{
			table[i].resize(A.size());
		}

		for (int i = 0; i < A.size(); ++i)
		{
			std::string &str = A[i];
			for (int j = 0; j < str.size(); ++j)
			{
				table[str[j] - 'a'][i] += 1;
			}
		}

		std::vector<std::string> ans;

		int min = INT_MAX;

		for (int ch = 0; ch < 26; ++ch)
		{
			for (int i = 0; i < table[ch].size(); ++i)
			{
				if (table[ch][i] < min)
				{
					min = table[ch][i];
				}
			}

			for (int i = 0; i < min; ++i)
			{
				ans.push_back(std::string(1, ch + 'a'));
			}
			min = INT_MAX;
		}
		return ans;
	}
};
}
#endif //__1002_FIND_COMMON_CHARS_H__
#pragma once

/*
	String Compression :		Perform basic string compression, using counts of repeated characters
							Example :	Input -> aabcccccaaa
										Ouput -> a2b1c5a3	[output length should be smaller than input, if not return input as it is]
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
	string countCompress(string &str)
	{
		if (str.size() < 2)
			return str;

		string ans;

		int i = 1;
		char lastChar = str[0];
		int count = 1;
		while (i < str.size())
		{
			if (str[i] == lastChar)
			{
				count++;
			}
			else
			{
				ans.push_back(lastChar);
				ans += to_string(count);
				count = 1;
				lastChar = str[i];
			}
			i++;
		}

		ans.push_back(lastChar);
		ans += to_string(count);

		return ans.size() < str.size() ? ans : str;
	}
};

int main()
{
	Solution sol;

	string str("aabcccccaaa");

	cout << sol.countCompress(str) << endl;
	return 0;
}
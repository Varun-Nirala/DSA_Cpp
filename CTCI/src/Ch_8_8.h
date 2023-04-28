#pragma once

/*
	Permutations with duplicates :	Write a method to compute all permutations of a string whose characters are not necessarily unqiue.
									The list of permutations should not have duplicates
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Solution_8_8
{
	void getAllPerms(map<char, int> &freq, string prefix, int remaining, vector<string> &results)
	{
		if (remaining == 0)
		{
			results.push_back(prefix);
			return;
		}

		for (auto &x : freq)
		{
			int count = x.second;
			if (count > 0)
			{
				freq[x.first] = count - 1;
				getAllPerms(freq, prefix + x.first, remaining - 1, results);
				freq[x.first] = count;
			}
		}
	}
public:
	vector<string> getUniquePerms(string str)
	{
		map<char, int> freq;
		for (auto &x : str)
			freq[x]++;

		vector<string> result;
		getAllPerms(freq, "", (int)str.size(), result);
		return result;
	}
};

void test_Ch_8_8()
{
	Solution_8_8 sol;

	vector<string> permutations = sol.getUniquePerms("aabbbbc");

	for (auto &x : permutations)
	{
		cout << x << endl;
	}
}
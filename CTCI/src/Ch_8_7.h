#pragma once

/*
	Permutations without duplicates :	Write a method to compute all permutations
										of a string of unique characters.
*/


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
	// Approach 1 : Building from permutation of first n-1 characters
	vector<string> getPerms_1(string str)
	{
		vector<string> permutatios;

		if (str.empty())
		{
			permutatios.push_back("");
			return permutatios;
		}

		char first = str[0];
		string remainder = str.substr(1);

		vector<string> words = getPerms_1(remainder);

		for (auto x : words)
		{
			for (int i = 0; i <= x.size(); ++i)
			{
				string s = x;
				s.insert(s.begin() + i, first);
				permutatios.push_back(s);
			}
		}
		return permutatios;
	}

	// Approach 2 : Building from permutation of all n-1 character substrings
	vector<string> getPerms_2(string remainder)
	{
		int size = remainder.size();

		vector<string> result;

		if (size == 0)
		{
			result.push_back("");
			return result;
		}

		for (int i = 0; i < size; ++i)
		{
			string before = remainder.substr(0, i);
			string after = remainder.substr(i + 1);

			vector<string> partials = getPerms_2(before + after);

			for (auto &x : partials)
			{
				result.push_back(remainder[i] + x);
			}
		}
		return result;
	}
};

int main()
{
	Solution sol;

	vector<string> permutations = sol.getPerms_2("abc");

	for (auto &x : permutations)
	{
		cout << x << endl;
	}

	return 0;
}

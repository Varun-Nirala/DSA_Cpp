#pragma once

/*
	Group Anagrams :		Write a method to sort an array of strings so that all the anagrams are next to each other.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution
{
public:
	void groupAnagrams(vector<string> &vec)
	{
		map<string, vector<string>> mm;

		for (auto &s : vec)
		{
			string key = s;
			sort(key.begin(), key.end());
			mm[key].push_back(s);
		}

		int id = 0;
		for (auto &val : mm)
		{
			vector<string> ll = val.second;
			for (auto &x : ll)
			{
				vec[id] = x;
				id++;
			}
		}
	}
};

int main()
{
	Solution sol;
	vector<string> vec = { "acre", "dog", "care", "god", "race", "ogd", "bali", "ilba" };

	sol.groupAnagrams(vec);

	for (auto x : vec)
	{
		cout << x << " ";
	}
	cout << endl;
	return 0;
}


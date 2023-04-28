#pragma once

/*
	Power set :	Write an algorithm to return all subset of a set.
*/

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Solution_8_4
{
	list<list<char>> powerSetUtil(vector<char> &vec, int index)
	{
		list<list<char>> allSubsets;

		if (index == vec.size())
			allSubsets.push_back({});	// Add empty subset base condition
		else
		{
			allSubsets = powerSetUtil(vec, index + 1);
			char ch = vec[index];

			list<list<char>> moreSubsets;
			for (auto x : allSubsets)
			{
				x.push_back(ch);
				moreSubsets.push_back(x);
			}
			allSubsets.insert(allSubsets.end(), moreSubsets.begin(), moreSubsets.end());
		}
		return allSubsets;
	}
public:
	list<list<char>> powerSet(vector<char> &vec)
	{
		return powerSetUtil(vec, 0);
	}
};

void test_Ch_8_4()
{
	vector<char> vec({ 'a', 'b', 'c', 'd', 'e', 'f' });
	Solution_8_4 sol;

	list<list<char>> allset = sol.powerSet(vec);

	for (auto &oneSet : allset)
	{
		for (auto &ch : oneSet)
		{
			cout << ch << " ";
		}
		cout << endl;
	}
}
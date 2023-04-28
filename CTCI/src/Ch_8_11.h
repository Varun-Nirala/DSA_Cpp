#pragma once

/*
	Coins :	Given an infinite number of quarters (25 cents), dimes (10 cents), nickels (5 cents), and pennies (1 cent),
			Write code to calculate the number of ways representing n cents.
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Solution_8_11
{
	int makeChangeutil(int amount, const vector<int> &denoms, int index, vector<vector<int>> &mm)
	{
		if (mm[amount][index] > 0)
			return mm[amount][index];

		if (index >= denoms.size() - 1)
			return 1;	// last denom

		int denomAmount = denoms[index];
		int ways = 0;
		for (int i = 0; i * denomAmount <= amount; ++i)
		{
			int amountRemaining = amount - i * denomAmount;
			ways += makeChangeutil(amountRemaining, denoms, index + 1, mm);
		}
		mm[amount][index] = ways;
		return ways;
	}
public:
	int makeChange(int n)
	{
		vector<int> denoms = { 25, 10, 5, 1 };
		vector<vector<int>> mm(n + 1);

		for (auto &x : mm)
		{
			x.resize(denoms.size());
		}
		return makeChangeutil(n, denoms, 0, mm);
	}
};

void test_Ch_8_11()
{
	Solution_8_11 sol;

	cout << sol.makeChange(100);
}
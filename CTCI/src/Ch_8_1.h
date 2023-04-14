#pragma once

/*
	Triple Step :	A child is running up a staircase with n steps and can hop either 1, 2 or 3 steps at a time.
					Implement a method to count how many possible ways the child can run up the stairs.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <map>

using namespace std;

class Solution
{
public:
	int countPossibleWays(int n)	// O(pow(3, n))
	{
		if (n < 0)
			return 0;
		else if (n == 0)
			return 1;
		else
		{
			return countPossibleWays(n - 1) + countPossibleWays(n - 2) + countPossibleWays(n - 3);
		}
	}

	int countPossibleWaysOptimized(int n)
	{
		vector<int> memo(n + 1, -1);
		return countUtil(n, memo);
	}
private:
	int countUtil(int n, vector<int> &memo)
	{
		if (n < 0)
			return 0;
		else if (n == 0)
			return 1;
		else if (memo[n] > -1)
		{
			return memo[n];
		}
		else
		{
			memo[n] = countUtil(n - 1, memo) + countUtil(n - 2, memo) + countUtil(n - 3, memo);
			return memo[n];
		}
	}
};

int main()
{
	Solution sol;

	for (int i = 0; i < 37; ++i)
	{
		int val1 = sol.countPossibleWays(i);
		int val2 = sol.countPossibleWaysOptimized(i);

		if (val1 != val2)
		{
			cout << "i = " << i << ", Failed ";
		}
		else
		{
			cout << "i = " << i << ", Passed ";
		}

		cout << val1 << ", " << val2 << endl;
	}

	return 0;
}

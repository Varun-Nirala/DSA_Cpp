#pragma once

/*
	Factorial Zeros :	Write an algorithm which computes the number of trailing zeros in n fatorial
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution_16_5
{
	int factorsOf5(int num)
	{
		int count = 0;
		while (num % 5 == 0)
		{
			count++;
			num /= 5;
		}
		return count;
	}
public:
	int countTrailingZerosInFactorial_1(int n)
	{
		int count = 0;
		for (int i = 5; i <= n; i += 5)
		{
			count += factorsOf5(i);
		}
		return count;
	}

	int countTrailingZerosInFactorial_2(int n)
	{
		int count = 0;

		if (n < 0)
			return -1;

		for (int i = 5; n / i > 0; i *= 5)
		{
			count += n / i;
		}
		return count;
	}
};

void test_Ch_16_5()
{
	Solution_16_5 sol;

	for (int i = 1; i < 31; ++i)
	{
		cout << "Number of trailing zeros in " << i << "! is " << sol.countTrailingZerosInFactorial_1(i) << endl;
	}
}
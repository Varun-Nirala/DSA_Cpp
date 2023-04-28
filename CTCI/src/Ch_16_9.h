#pragma once

/*
	Operations :		Write methods to implement the multiply, subtract and divide operations for integers. The results of all these
					are integers. Use only add operator
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Solution_16_9
{
	int negate(int num)
	{
		/* How it works. Example is for positive number as input, but it works same for negative number
		* idea is to bring positive number to 0 by adding negative delta to it, and doubling up delta each time until num and num - delta have same sign
		* num	: 29		28	26	22	14	13	11	7	6	4	0
		* delta	: -1		-2	-4	-8	-1	-2	-4	-1	-2	-4
		*/

		int neg = 0;
		int newSign = num < 0 ? 1 : -1;

		int delta = newSign;
		while (num != 0)
		{
			bool diffsigns = ((num + delta) > 0) != (num > 0);
			if (num + delta != 0 && diffsigns)	// if delta is too big reset it 
			{
				delta = newSign;
			}
			neg += delta;
			num += delta;
			delta += delta;
		}
		return neg;
	}

	int giveAbs(int num)
	{
		if (num < 0)
		{
			return negate(num);
		}
		return num;
	}

public:
	int subtact(int a, int b)
	{
		return a + negate(b);
	}

	int multiply(int a, int b)
	{
		if (a < b)
		{
			return multiply(b, a);
		}
		// Now we have a > b
		int sum = 0;

		for (int i = giveAbs(b); i > 0; i = subtact(i, 1))
		{
			sum += a;
		}

		if (b < 0)
		{
			sum = negate(sum);
		}
		return sum;
	}

	int divide(int a, int b)
	{
		/*	X = a / b;
		*	a = Xb;
		*	or we can add b x times
		*/
		if (b == 0)
			throw std::overflow_error("Divide by zero exception");

		int absa = giveAbs(a);
		int absb = giveAbs(b);

		int product = 0;
		int x = 0;
		while (product + absb <= absa)
		{
			product += absb;
			x++;
		}

		if ((a < 0 && b < 0) || (a > 0 && b > 0))
		{
			return x;
		}
		else
		{
			return negate(x);
		}
	}
};

void test_Ch_16_9()
{
	Solution_16_9 sol;

	int a = 10;
	int b = -11;

	cout << "( " << a << " )" << " + " << "( " << b << " )" << " => " << a + b << endl;
	cout << "( " << a << " )" << " - " << "( " << b << " )" << " => " << sol.subtact(a, b) << endl;
	cout << "( " << a << " )" << " * " << "( " << b << " )" << " => " << sol.multiply(a, b) << endl;
	cout << "( " << a << " )" << " / " << "( " << b << " )" << " => " << sol.divide(a, b) << endl;
}
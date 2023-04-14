/* 	HackerRank :: Fundamentals -> Summing the N Series 
	Nth Term given by 	-> Tn = n^2 - (n-1)^2
	Sum of Series		-> Sn = T1 + T2 + T3 + ... + Tn

	Work :: 
		Tn can be deduced to
			Tn = 2n - 1;
			Sn = (n(T1 + Tn))/2 => n*n
*/

#include <iostream>
#include <cmath>

using namespace std;

typedef long long int longInt;

longInt divisorForMod = 1000000007;

longInt CalSumOfSeries(longInt n)
{
	longInt ans = ((n%divisorForMod)*(n%divisorForMod))%divisorForMod;
	return ans;
}

void test_summingTheN_Series()
{
	int testCase;
	longInt	n;
	longInt sumOfSeries = 0;

	cin >> testCase;

	while(testCase--)
	{
		cin >> n;
		sumOfSeries = CalSumOfSeries(n);
		cout << sumOfSeries << endl;
	}
}
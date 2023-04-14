/* HackerRank : Cutting Paper Squares */
#include <iostream>

using namespace std;

long int solve(long int n, long int m)
{
	return (n*m)-1;
}

void test_cuttingPaperSquares()
{
    long int n;
    long int m;
    cin >> n >> m;
    long int result = solve(n, m);
    cout << result << endl;
}
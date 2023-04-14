/*Given integers b and a, find the smallest integer h, such that there exists a triangle of height h, base b, having an area of at least a.

Input Format
	In the first and only line, there are two space-separated integers b and a, denoting respectively the base of a triangle and the desired minimum area.
Output Format
	In a single line, print a single integer h, denoting the minimum height of a triangle with base b and area at least a.
*/
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int findMinHeightOfTriangle(int base, int area)
{
	int rem = 0;
	int height = 0;

	int count = 0;
	area = area*2;
	while(count < 10)
	{
		rem = area % base;
		if(rem == 0)
		{
			height = area / base;
			break;
		}
		else
		{
			area = area - rem + base;
		}
		count++;
	}
	return height;
}

void test_smallestHeightTriangle()
{
	int base, area, height;

	cin >> base >> area;

	height = findMinHeightOfTriangle(base, area);

	cout << height << endl;

	system("PAUSE");
}
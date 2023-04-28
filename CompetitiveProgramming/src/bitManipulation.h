#include <iostream>

using namespace std;

using L_INT = long long int;

string convertIntToBinary(L_INT number)
{
	int numberOfDigit = 1;
	int temp = 2;
	string s;

	if(number == 0)
	{
		return "0";
	}

	while(number >= temp)
	{
		numberOfDigit++;
		temp = temp*2;
	}

	s.resize(numberOfDigit);

	while(number)
	{
		s[--numberOfDigit] = number%2 + '0';
		number = number/2;
	}
	return s;
}

L_INT convertBinaryToInt(const string &s)
{
	int size = (int)s.size();
	int i = 0;
	int number = 0;

	while(size--)
	{
		number = number + ((int)pow(2, i) * (s[size] - '0'));
		i++;
	}
return number;
}

void test_bitManipulation()
{
	L_INT number;
	string s;

	while(1)
	{
		cout << "Enter a number : ";
		cin >> number;

		s = convertIntToBinary(number);

		number = convertBinaryToInt(s);
	}
}
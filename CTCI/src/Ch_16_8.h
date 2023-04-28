#pragma once

/*
	English Int :	Given any integer, print an English phrase that describes the integer 
						(e.g., "One Thousand, Two Hundred Thirty Four")
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Solution_16_8
{
	const vector<string> smalls = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven",
								"Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

	const vector<string> tens = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

	const vector<string> bigs = { "", "Thousand", "Million", "Billion" };

	const string hundred = "Hundred";
	const string negative = "Negative";

private:
	string listToString(list<string> &ll)
	{
		string s;
		while (ll.size() > 1)
		{
			s += (ll.front() + " ");
			ll.pop_front();
		}
		s += ll.front();
		ll.pop_front();
		return s;
	}

	string convertChunk(int number)
	{
		list<string> parts;

		/*Convert hundred place*/
		if (number >= 100)
		{
			parts.push_back(smalls[number / 100]);
			parts.push_back(hundred);
			number %= 100;
		}

		/*Convert tens place*/
		if (number >= 10 && number <= 19)
		{
			parts.push_back(smalls[number]);
		}
		else if (number >= 20)
		{
			parts.push_back(tens[number / 10]);
			number %= 10;
		}

		/*Convert ones place */
		if (number >= 1 && number <= 9)
		{
			parts.push_back(smalls[number]);
		}

		return listToString(parts);
	}

public:
	string convert(int num)
	{
		if (num == 0)
		{
			return smalls[num];
		}
		else if (num < 0)
		{
			return negative + " " + convert(-1 * num);
		}

		list<string> parts;
		int chunkcount = 0;

		const int thousand = 1000;

		while (num > 0)
		{
			if (num % thousand != 0)
			{
				string chunk = convertChunk(num % thousand) + " " + bigs[chunkcount];
				parts.push_front(chunk);
			}
			num /= thousand;
			chunkcount++;
		}

		return listToString(parts);
	}
};

void test_Ch_16_8()
{
	Solution_16_8 sol;

	int num = -19'235;
	cout << num << " => " << sol.convert(num) << endl;
}
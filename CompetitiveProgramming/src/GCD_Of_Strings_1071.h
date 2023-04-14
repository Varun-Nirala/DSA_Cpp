#ifndef __GCD_OF_STRINGS_1071_H__
#define __GCD_OF_STRINGS_1071_H__

#include <iostream>
#include "helper.h"

namespace nsCP
{
class Solution1071
{
public:
	void test()
	{
		printf("Test : Solution1071 -> GCD of strings : START\n");
		std::vector<std::string> inp1{ "ABCABC", "ABABAB", "LEET", "ABCDEF"};
		std::vector<std::string> inp2{ "ABC", "ABAB", "CODE", "ABC"};
		std::vector<std::string> expectedOutput{"ABC", "AB", "", ""};

		int failed = 0;
		for (size_t i = 0; i < inp1.size(); ++i)
		{
			if (gcdOfStrings(inp1[i], inp2[i]) != expectedOutput[i])
			{
				failed++;
			}
		}
		print("GCD of Strings", inp1.size(), failed);
		printf("Test : Solution1071 -> GCD of strings : END\n\n");
	}

private:
	std::string gcdOfStrings(std::string str1, std::string str2) {
		std::string &bigString = str1.size() > str2.size() ? str1 : str2;
		std::string &smallString = str1.size() > str2.size() ? str2 : str1;

		for (size_t i = smallString.size(); i > 0; --i)
		{
			if (itDivide(smallString, smallString.substr(0, i)))
			{
				if (itDivide(bigString, smallString.substr(0, i)))
				{
					return smallString.substr(0, i);
				}
			}
		}
		return "";
	}

	bool itDivide(const std::string &big, const std::string &small)
	{
		if (big.size() % small.size() != 0)
			return false;

		for (size_t i = 0; i < big.size(); i += small.size())
		{
			size_t start = i;
			for (size_t j = 0; j < small.size(); ++j)
			{
				if (big[start++] != small[j])
					return false;
			}
		}
		return true;
	}
};
}
#endif // #ifndef __GCD_OF_STRINGS_1071_H__
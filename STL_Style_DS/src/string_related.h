#ifndef __STRING_RELATED_H__
#define __STRING_RELATED_H__

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include "Common/helper.h"

namespace ns_Util
{
class Strings
{
public:
	// Permutations
	std::vector<std::string> getAllPermutations_1(std::string& str);
	std::vector<std::string> getAllPermutations_2(std::string& str);
	bool getNextPermutations(std::string& str);

	// Longest Common Subsequence
	std::string findLCS(const std::string& strM, const std::string& strN, bool useIterative);

	// Knuth–Morris–Pratt[KMP] pattern searching
	std::vector<size_t> findSubStrKMP(const std::string& str, const std::string& pattern);
private:
	std::vector<int> buildLPS(const std::string& pattern);	// Longest prefix suffix

	std::string getLCS_iterative(const std::vector<std::vector<int>>& dp, const std::string& strM, const std::string& strN);
	std::string getLCS_recursive(const std::vector<std::vector<int>>& dp, const std::string& strM, const std::string& strN, size_t i, size_t j);
private:
	static const std::string		m_className;
};
const std::string Strings::m_className{ "Strings : " };

// ************************************************ Permutations ************************************************ //
std::vector<std::string> Strings::getAllPermutations_1(std::string& str)
{
	LOG_ENTRY_CLASS;
	std::vector<std::string> vec;
	std::function<void(std::string&, size_t, size_t)> func;
	func = [&vec, &func](std::string& s, size_t start, size_t end) -> void {
		if (start == end)
		{
			vec.push_back(s);
			return;
		}
		for (size_t i = start; i <= end; ++i)
		{
			std::swap(s[i], s[start]);
			func(s, start + 1, end);
			std::swap(s[i], s[start]);
		}
	};

	func(str, 0, str.size() - 1);
	LOG_EXIT_CLASS;

	return vec;
}

std::vector<std::string> Strings::getAllPermutations_2(std::string& str)
{
	LOG_ENTRY_CLASS;
	std::vector<std::string> vec;
	std::function<void(std::string&, std::string)> func;

	func = [&vec, &func](std::string& s, std::string prefix) -> void {
		if (s.empty())
		{
			vec.push_back(prefix);
			return;
		}
		for (size_t i = 0; i < s.size(); ++i)
		{
			std::string rem = s.substr(0, i) + s.substr(i + 1);
			func(rem, prefix + s[i]);
		}
	};

	func(str, "");
	LOG_EXIT_CLASS;
	return vec;
}


/* Next permutation steps
1) An sequence sorted in descending order does not have next permutation. For example "edcba” does not have next permutation.

2) For a sequence which is not sorted in descending order for example “abedc”, we can follow below steps :
	.a) Traverse from right and find the first item that is not following the descending order.
		For example in “abedc”, the character ‘b’ does not follow the descending order.
	.b) Swap the found character with closest greater (or smallest greater) element on right side of it.
		In case of “abedc”, we have ‘c’ as the closest greater element.
			After swapping ‘b’ and ‘c’, string becomes “acedb”.
	.c) After swapping, sort the string after the position of character found in step a.
		After sorting the substring “edb” of “acedb”, we get “acbde” which is the required next permutation.

Optimizations in step b) and c)
a) Since the sequence is sorted in decreasing order, we can use binary search to find the closest greater element.
c) Since the sequence is already sorted in decreasing order (even after swapping as we swapped with the closest greater),
	we can get the sequence sorted (in increasing order) after reversing it.
*/
bool Strings::getNextPermutations(std::string& str)
{
	LOG_ENTRY_CLASS;
	int size = str.size();
	int i = size - 2;
	bool retVal = true;
	while (i >= 0 && str[i] >= str[i + 1])
	{
		--i;
	}

	if (i < 0)
	{
		retVal = false;
	}
	else
	{
		int index = size - 1;

		while (str[index] < str[i])
		{
			index--;
		}
		std::swap(str[i], str[index]);

		std::reverse(str.begin() + i + 1, str.end());
	}
	LOG_EXIT_CLASS;
	return retVal;
}

// ************************************************ Longest Common Subsequence ************************************************ //

std::string Strings::getLCS_iterative(const std::vector<std::vector<int>>& dp, const std::string& strM, const std::string& strN)
{
	std::string subStr;
	size_t i = strM.size();
	size_t j = strN.size();

	subStr.resize(dp[i][j]);
	size_t index = subStr.size();

	while (i > 0 && j > 0)
	{
		if (strM[i - 1] == strN[j - 1])
		{
			subStr[--index] = strM[i - 1];
			--i;
			--j;
		}
		else if (dp[i - 1][j] > dp[i][j - 1])
		{
			--i;
		}
		else
		{
			--j;
		}
	}
	return subStr;
}

std::string Strings::getLCS_recursive(const std::vector<std::vector<int>>& dp, const std::string& strM, const std::string& strN, size_t i, size_t j)
{
	if (i == 0 || j == 0)
	{
		return "";
	}

	if (strM[i - 1] == strN[j - 1])
	{
		return getLCS_recursive(dp, strM, strN, i - 1, j - 1) + strM[i - 1];
	}
	else if (dp[i][j - 1] > dp[i - 1][j])
	{
		return getLCS_recursive(dp, strM, strN, i, j - 1);
	}
	return getLCS_recursive(dp, strM, strN, i - 1, j);
}

std::string Strings::findLCS(const std::string& strM, const std::string& strN, bool useIterative)
{
	const size_t rows = strM.size() + 1;
	const size_t cols = strN.size() + 1;

	std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, 0));

	for (size_t i = 1; i < rows; ++i)
	{
		for (size_t j = 1; j < cols; ++j)
		{
			if (strM[i - 1] == strN[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else
			{
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	return useIterative ? getLCS_iterative(dp, strM, strN) : getLCS_recursive(dp, strM, strN, rows - 1, cols - 1);

	//cout << findLCS("XMJYAUZ", "MZJAWXU") << endl;
	//cout << findLCS("GAC", "AGCAT") << endl;
	//cout << findLCS("AGGTAB" , "GXTXAYB") <<  endl;
	//cout << findLCS("ABCDGH", "AEDFHR") << endl;
}


// ************************************************ Knuth–Morris–Pratt[KMP] pattern searching ************************************************ //
std::vector<int> Strings::buildLPS(const std::string& pattern)	// Longest prefix suffix
{
	const size_t patSize = pattern.size();
	std::vector<int> lps(patSize, 0);

	int length = 0;
	size_t i = 1;
	while (i < patSize)
	{
		if (pattern[i] == pattern[length])
		{
			lps[i++] = ++length;
		}
		else
		{
			if (length != 0)
			{
				length = lps[length - 1];
			}
			else
			{
				lps[i++] = 0;
			}
		}
	}
	return lps;
}


std::vector<size_t> Strings::findSubStrKMP(const std::string& str, const std::string& pattern)
{
	std::vector<size_t> matchIndexes;
	std::vector<int> lps = buildLPS(pattern);

	const size_t strSize = str.size();
	const size_t patSize = pattern.size();
	size_t strId = 0;
	size_t patId = 0;

	while (strId < strSize)
	{
		if (str[strId] == pattern[patId])
		{
			strId++;
			patId++;
		}

		if (patId == patSize)
		{
			matchIndexes.push_back(strId - patId);
			patId = lps[patId - 1];
		}
		else if (strId < strSize && str[strId] != pattern[patId])
		{
			if (patId != 0)
			{
				patId = lps[patId - 1];
			}
			else
			{
				strId++;
			}
		}
	}
	return matchIndexes;

	// cout << subStrSearch("abxabcabcaby", "abcaby") << endl;
}



// ************************************************ TEST ************************************************ //

bool test_getAllPermutations_1(std::vector<std::string> &inputs, std::vector<std::vector<std::string>> expectedOutput, size_t dataSize, int testNum)
{
	LOG_ENTRY;
	const char* testName = "Permutations via swap";

	Strings stringsObj;
	for (size_t i = 0; i < dataSize; ++i)
	{
		std::vector<std::string> allPers = stringsObj.getAllPermutations_1(inputs[i]);
		std::pair<std::pair<size_t, size_t>, bool> p = findMismatch<std::string>(expectedOutput[i], allPers);

		if (p.second)
		{
			TEST_PASS;
		}
		else
		{
			TEST_FAIL;
			ns_Util::Logger::LOG_MSG("\nInput String = ", inputs[i], ", Expected permutation Count = ", expectedOutput[i].size(), ", Output permutation Count = ", allPers.size());
			ns_Util::Logger::LOG_MSG(", Got mismatch at Expected index = ", p.first.first, ", Output Index = ", p.first.second, "\n\n");
			ASSERT;
			return false;
		}
	}
	return true;
}

bool test_getAllPermutations_2(std::vector<std::string>& inputs, std::vector<std::vector<std::string>> expectedOutput, size_t dataSize, int testNum)
{
	LOG_ENTRY;
	const char* testName = "Permutations via prefix";

	Strings stringsObj;
	for (size_t i = 0; i < dataSize; ++i)
	{
		std::vector<std::string> allPers = stringsObj.getAllPermutations_2(inputs[i]);
		std::pair<std::pair<size_t, size_t>, bool> p = findMismatch<std::string>(expectedOutput[i], allPers);

		if (p.second)
		{
			TEST_PASS;
		}
		else
		{
			TEST_FAIL;
			ns_Util::Logger::LOG_MSG("\nInput String = ", inputs[i], ", Expected permutation Count = ", expectedOutput[i].size(), ", Output permutation Count = ", allPers.size());
			ns_Util::Logger::LOG_MSG(", Got mismatch at Expected index = ", p.first.first, ", Output Index = ", p.first.second, "\n\n");
			ASSERT;
			return false;
		}
	}
	return true;
}

bool test_getNextPermutations(std::vector<std::string>& inputs, std::vector<std::vector<std::string>> expectedOutput, size_t dataSize, int testNum)
{
	LOG_ENTRY;
	const char* testName = "Permutations via nextPermutation";

	Strings stringsObj;
	for (size_t i = 0; i < dataSize; ++i)
	{
		std::string str = inputs[i];

		std::vector<std::string>& output = expectedOutput[i];
		size_t j = 0;
		bool foundNextPermutation = true;
		while (foundNextPermutation)
		{
			if (j < output.size() && str != output[j])
			{
				TEST_FAIL;
				ns_Util::Logger::LOG_MSG("\nInput String = ", inputs[i], ", permutation count = ", j, ", Expected next permutation = ", output[j], ", Output next permutation = ", str, "\n\n");
				ASSERT;
				return false;
			}
			foundNextPermutation = stringsObj.getNextPermutations(str);
			++j;
		}
		if (j == output.size())
		{
			TEST_PASS;
		}
		else
		{
			TEST_FAIL;
			ns_Util::Logger::LOG_MSG("\nInput String = ", inputs[i], ", Expected permutation count = ", output.size(), ", output permutation count = ", j, "\n\n");
			ASSERT;
			return false;
		}
	}
	return true;
}

bool test_Permutations()
{
	LOG_ENTRY;
	const char* testName = "String Permutations";
	size_t dataSize = 6;

	int testNum = 1;
	std::vector<std::string> inputs(5);
	inputs[0] = "cd";
	inputs[1] = "abb";
	inputs[2] = "abc";
	inputs[3] = "geek";
	inputs[4] = "abcd";
	inputs[5] = "abcde";

	std::vector<std::vector<std::string>> expectedOutput(dataSize);
	expectedOutput[0] = { "cd", "dc" };
	expectedOutput[1] = { "abb", "abb", "bab", "bba", "bab", "bba" };
	expectedOutput[2] = { "abc", "acb", "bac", "bca", "cba", "cab" };
	expectedOutput[3] = { "geek", "geke", "gkee", "egek", "egke", "eegk", "eekg", "ekge", "ekeg", "kgee", "kege", "keeg" };
	expectedOutput[4] = { "abcd", "bacd", "cabd", "acbd", "bcad", "cbad", "cbda", "bcda", "dcba", "cdba", "bdca", "dbca", "dacb", "adcb", "cdab", "dcab", "acdb", "cadb", "badc", "abdc", "dbac", "bdac", "adbc", "dabc" };
	expectedOutput[5] = { "abcde", "bacde", "cabde", "acbde", "bcade", "cbade", "cbdae", "bcdae", "dcbae", "cdbae",
							"bdcae", "dbcae", "dacbe", "adcbe", "cdabe", "dcabe", "acdbe", "cadbe", "badce", "abdce",
							"dbace", "bdace", "adbce", "dabce", "eabcd", "aebcd", "beacd", "ebacd", "abecd", "baecd",
							"baced", "abced", "cbaed", "bcaed", "acbed", "cabed", "cebad", "ecbad", "bcead", "cbead",
							"ebcad", "becad", "aecbd", "eacbd", "caebd", "acebd", "ecabd", "ceabd", "deabc", "edabc",
							"adebc", "daebc", "eadbc", "aedbc", "aebdc", "eabdc", "baedc", "abedc", "ebadc", "beadc",
							"bdaec", "dbaec", "abdec", "badec", "dabec", "adbec", "edbac", "debac", "bedac", "ebdac",
							"dbeac", "bdeac", "cdeab", "dceab", "ecdab", "cedab", "decab", "edcab", "edacb", "deacb",
							"aedcb", "eadcb", "daecb", "adecb", "acedb", "caedb", "eacdb", "aecdb", "ceadb", "ecadb",
							"dcaeb", "cdaeb", "adceb", "daceb", "cadeb", "acdeb", "bcdea", "cbdea", "dbcea", "bdcea",
							"cdbea", "dcbea", "dceba", "cdeba", "edcba", "decba", "cedba", "ecdba", "ebdca", "bedca",
							"debca", "edbca", "bdeca", "dbeca", "cbeda", "bceda", "ecbda", "cebda", "becda", "ebcda" };
	
	TEST_TYPE(" : Using swapping\n");
	if (!test_getAllPermutations_1(inputs, expectedOutput, dataSize, testNum))
	{
		return false;
	}
	testNum++;

	TEST_TYPE(" : Using prefix\n");
	if (!test_getAllPermutations_2(inputs, expectedOutput, dataSize, testNum))
	{
		return false;
	}
	testNum++;

	TEST_TYPE(" : Calling nextPermutation \n");
	if (!test_getNextPermutations(inputs, expectedOutput, dataSize, testNum))
	{
		return false;
	}
	testNum++;

	LOG_EXIT;
	ns_Util::Logger::LOG_MSG("#####################################\n");
	return true;
}

}	// namespace ns_Util

#endif // #ifndef __STRING_RELATED_H__
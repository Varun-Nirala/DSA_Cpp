#ifndef __POWER_SET_H__
#define __POWER_SET_H__

#include <vector>
#include <iostream>
#include "Common/helper.h"
#include "Common/logger.h"

namespace ns_Util {
// ******************* ALGO 1 - START ******************* //
std::vector<std::vector<char>> powerSet_Algo1(std::vector<char>& vec, int id = 0)
{
	std::vector<std::vector<char>> allSubSets;

	if (id == vec.size())
	{
		allSubSets.push_back({});
	}
	else
	{
		allSubSets = powerSet_Algo1(vec, id + 1);
		char val = vec[id];

		std::vector<std::vector<char>> moreSubSets;
		for (auto x : allSubSets)
		{
			x.push_back(val);
			moreSubSets.push_back(x);
		}
		allSubSets.insert(allSubSets.end(), moreSubSets.begin(), moreSubSets.end());
	}

	return allSubSets;
}
// ******************* ALGO 1 - END ******************* //


// ******************* ALGO 2 - START ******************* //
std::vector<std::vector<char>> powerSet_Algo2(std::vector<char> vec)
{
	std::vector<std::vector<char>> allSet;
	if (vec.empty())
	{
		allSet.push_back({});
	}
	else
	{
		char ch = vec.front();
		vec.erase(vec.begin());
		allSet = powerSet_Algo2(vec);
		std::vector<std::vector<char>> moreSet;
		for (auto v : allSet)
		{
			v.push_back(ch);
			moreSet.push_back(v);
		}
		allSet.insert(allSet.end(), moreSet.begin(), moreSet.end());
	}
	return allSet;
}

// ******************* ALGO 2 - END ******************* //
void test_PowerSet_1()
{
	std::vector<char> vec({ 'a', 'b', 'c', 'd', 'e', 'f' });
	const char* testName = "PowerSet";

	ns_Util::Logger::LOG_MSG("Executing Algo 1 : ", testName, '\n');
	std::vector<std::vector<char>> result_algo_1 = powerSet_Algo1(vec);

	for (auto& oneSet : result_algo_1)
	{
		ns_Util::printVector(oneSet);
	}
	ns_Util::Logger::LOG_MSG("\n\n");

	ns_Util::Logger::LOG_MSG("Executing Algo 2 : ", testName, '\n');
	std::vector<std::vector<char>> result_algo_2 = powerSet_Algo2(vec);
	
	for (auto& oneSet : result_algo_2)
	{
		ns_Util::printVector(oneSet);
	}
	ns_Util::Logger::LOG_MSG("\n\n");

	if (result_algo_1 == result_algo_2)
	{
		ns_Util::Logger::LOG_MSG("PASS\n\n");
	}
	else
	{
		ns_Util::Logger::LOG_MSG("FAIL\n\n");
	}
}

void test_PowerSet()
{
	LOG_ENTRY;
	test_PowerSet_1();
	LOG_EXIT;
	ns_Util::Logger::LOG_MSG("#####################################\n\n");
}

}	// namespace ns_Util

#endif	// #ifndef __POWER_SET_H__
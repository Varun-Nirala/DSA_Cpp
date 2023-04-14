#pragma once

#include "Common/testClass.h"
#include "Common/logger.h"
#include "Common/timer.h"
#include "Common/helper.h"

#include "dynamicArr.h"

#include "linkList.h"
#include "doublyLinkList.h"

#include "stackUsingVec.h"
#include "stackUsingList.h"

#include "queue.h"
#include "dequeueUsingList.h"
#include "dequeueUsingListOfVec.h"

template<typename T>
void compareVectorsSize(std::vector<T>& stlVector, DynamicArr<T>& dynamicArr)
{
	LOG_ENTRY;
	if (stlVector.size() != dynamicArr.size())
	{
		TEST_FAIL("Vector size comparision");
		ASSERT(false);
	}
	TEST_PASS("Vector size comparision");
	LOG_EXIT;
}

template<typename T>
void compareVectors(std::vector<T>& stlVector, DynamicArr<T>& dynamicArr)
{
	LOG_ENTRY;
	for (size_t i = 0; i < dynamicArr.size(); ++i)
	{
		if (stlVector[i] != dynamicArr[i])
		{
			TEST_FAIL_MSG("Vector data comparision", "At index", i);
			ASSERT(false);
		}
	}
	TEST_PASS("Vector data comparision");
	LOG_EXIT;
}

template<typename T>
void performRandomTestOnVector(std::vector<T>& stlVector, DynamicArr<T>& dynamicArr)
{
	LOG_ENTRY;

	// 1. Test resizing
	stlVector.resize(20);
	dynamicArr.resize(20);

	compareVectorsSize(stlVector, dynamicArr);

	// 2. Test clear
	stlVector.clear();
	dynamicArr.clear();
	compareVectorsSize(stlVector, dynamicArr);

	if (!stlVector.empty() || !dynamicArr.empty())
	{
		TEST_FAIL("Vector empty function");
	}
	else
	{
		TEST_PASS("Vector empty function");
	}

	// 3. Test push back
	size_t size = ns_Util::getRandomNumber(100, 500);
	for (size_t i = 0; i < size; ++i)
	{
		int data = ns_Util::getRandomNumber(0, INT_MAX);
		stlVector.push_back(T(data));
		dynamicArr.push_back(T(data));
	}
	compareVectorsSize(stlVector, dynamicArr);
	compareVectors(stlVector, dynamicArr);

	// 4. Test pop back
	while (!stlVector.empty())
	{
		if (stlVector.back() != dynamicArr.back())
		{
			TEST_FAIL("Vector pop_back function");
		}
		stlVector.pop_back();
		dynamicArr.pop_back();
	}
	compareVectorsSize(stlVector, dynamicArr);

	// 5. Test random erase
	size = ns_Util::getRandomNumber(100, 800);
	for (size_t i = 0; i < size; ++i)
	{
		int data = ns_Util::getRandomNumber(0, INT_MAX);
		stlVector.push_back(T(data));
		dynamicArr.push_back(T(data));
	}
	compareVectorsSize(stlVector, dynamicArr);
	compareVectors(stlVector, dynamicArr);

	size = ns_Util::getRandomNumber(100, stlVector.size() / 2);

	while (size-- > 0)
	{
		size_t index = ns_Util::getRandomNumber(0, stlVector.size() - 1);

		if (stlVector[index] != dynamicArr[index])
		{
			TEST_FAIL("Vector [] access function");
		}
		stlVector.erase(index);
		dynamicArr.erase(index);
	}
	compareVectorsSize(stlVector, dynamicArr);
	compareVectors(stlVector, dynamicArr);

	LOG_EXIT;
}

void test_dynamicArr()
{
	LOG_ENTRY;
	TEST_TYPE("Testing vector of TestClass of integers\n\n");

	std::vector<ns_Util::TestClass<int>> vec;
	DynamicArr<ns_Util::TestClass<int>> arr;

	arr.resize(10);
	vec.resize(10);

	compareVectorsSize(vec, arr);

	arr.clear();
	vec.clear();

	for (int i = 0; i < arr.size(); ++i)
	{
		vec.push_back(ns_Util::TestClass<int>(i + 1));
		arr.push_back(ns_Util::TestClass<int>(i + 1));
	}

	compareVectorsSize(vec, arr);

	compareVectors(vec, arr);

	for (int i = 0; i < 20; ++i)
	{
		arr.emplace_back(ns_Util::TestClass<int>(i * 40));
		vec.emplace_back(ns_Util::TestClass<int>(i * 40));
	}

	compareVectorsSize(vec, arr);

	compareVectors(vec, arr);

	arr.resize(arr.size() / 2);
	vec.resize(vec.size() / 2);

	compareVectorsSize(vec, arr);

	compareVectors(vec, arr);

	while (!arr.empty() && !vec.empty())
	{
		arr.pop_back();
		vec.pop_back();
		compareVectors(vec, arr);
	}

	compareVectorsSize(vec, arr);

	arr.clear();
	vec.clear();

	LOG_EXIT;
}

void test_LinkList()
{
	ns_Util::Logger::LOG_MSG("Testing LinkList\n\n");
	LinkList<int> ll;

	int max = 10;
	for (int i = 0; i < max; ++i)
	{
		ll.push_front(i + 1);
		ll.print();
	}

	ll.insert(0, 11);
	ll.insert(1, 12);

	max += 2;

	ll.print();

	ns_Util::Logger::LOG_MSG("\n\n");
	for (int i = 0; i < max; ++i)
	{
		ns_Util::Logger::LOG_MSG("Front : ", ll.front(), '\n');
		ll.pop_front();
		ll.print();
	}
}

void test_DoublyLinkList()
{
	ns_Util::Logger::LOG_MSG("Testing DoublyLinkList\n\n");
	DoublyLinkList<int> ll;

	int max = 10;
	for (int i = 0; i < max; ++i)
	{
		ll.push_front(i + 1);
		ll.print();
	}

	ll.insert(0, 11);
	ll.insert(1, 12);

	max += 2;

	ll.print();

	ns_Util::Logger::LOG_MSG("\n\n");
	for (int i = 0; i < max; ++i)
	{
		ns_Util::Logger::LOG_MSG("Front : ", ll.front(), '\n');
		ll.pop_front();
		ll.print();
	}
}
#pragma once

#include "DynamicArray.h"
#include "DoublyLinkList.h"
#include "stack.h"
#include "deque.h"
#include "queue.h"
#include "Permutation.h"

void TestPermute()
{
	using std::cin;
	using std::cout;
	using std::endl;

	cout << "STARTED TESTING : " << __FUNCTION__ << endl;
	std::string s = "abc";
	cout << "STRING : " << s << endl;
	permute(s, 0, 2);
	cout << "STARTED TESTING : " << __FUNCTION__ << endl;
}

void TestDS()
{
	TestDynamicArray();
	TestDoublyLinkList();
	TestStack();
	TestDeque();
	TestQueue();
}
#pragma once
/*
	Palindrome : Check if List is palindrome
*/

#include <iostream>
#include <vector>

#include <set>

#include "ds_list.h"

using namespace std;

class Solution_2_6
{
	ListNode *reverseAndClone(ListNode *head, int &size)
	{
		size = 0;
		ListNode *nList = nullptr;
		while (head)
		{
			size++;
			ListNode *node = new ListNode(head->val);
			node->next = nList;
			nList = node;

			head = head->next;
		}
		return nList;
	}

public:
	bool isPalindrome(ListNode *head)
	{
		if (!head || !head->next)
			return true;

		int size = 0;
		ListNode *revList = reverseAndClone(head, size);
		PrintList(revList);

		size = size / 2 + 1;
		while (size--)
		{
			if (head->val != revList->val)
				return false;

			head = head->next;
			revList = revList->next;
		}

		return true;
	}
};

void test_Ch_2_6()
{
	Solution_2_6 sol;
	vector<int> vec1({ 1, 2, 3, 2, 1 });
	vector<int> vec2({ 1, 2, 3, 3, 2, 1 });

	ListNode *head = createList(vec1);
	PrintList(head);

	cout << boolalpha << sol.isPalindrome(head) << endl;

	head = createList(vec2);
	PrintList(head);
	cout << boolalpha << sol.isPalindrome(head) << endl;
}

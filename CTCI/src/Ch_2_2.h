#pragma once

/*
	kth Element :	Given a list head, return kth from last elements
*/

#include <iostream>
#include <vector>

#include <set>

#include "ds_list.h"

using namespace std;

class Solution_2_2
{
public:
	ListNode* kthToLast(ListNode* head, int k)
	{
		ListNode *kthElemt = head;

		while (k-- && head)
		{
			head = head->next;
		}

		if (k >= 0)
			return nullptr;

		while (head)
		{
			head = head->next;
			kthElemt = kthElemt->next;
		}

		return kthElemt;
	}
};

void test_Ch_2_2()
{
	Solution_2_2 sol;

	ListNode *head = createList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 });

	int k = 4;
	cout << "Printing original list : ";
	PrintList(head);

	head = sol.kthToLast(head, 12);

	if (head)
	{
		cout << k << "th from last is : " << head->val;
	}
	else {
		cout << k << " is more than list length\n";
	}
}

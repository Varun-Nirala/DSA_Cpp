#pragma once
/*
	Remove Duplicates :	Given a list head, remove duplicate elements
						1. With using extra space
						2. Without using extra space
*/

#include <iostream>
#include <vector>
#include <set>

#include "ds_list.h"

using namespace std;

class Solution_2_1
{
public:
	ListNode* removeDuplicateUsingExtraSpace(ListNode* head)
	{
		if (!head || !head->next)
			return head;

		ListNode *n = head->next, *p = head;
		set<int> ss;
		ss.insert(p->val);

		while (n)
		{
			if (ss.count(n->val))
			{
				p->next = n->next;
				delete n;
				n = p;
			}
			else
			{
				ss.insert(n->val);
				p = n;
			}
			n = n->next;
		}
		return head;
	}

	ListNode* removeDuplicateWithoutUsingExtraSpace(ListNode* head)
	{
		if (!head || !head->next)
			return head;

		ListNode *outerNode = head;

		while (outerNode)
		{
			ListNode *innerNodePrev = nullptr;
			ListNode *innerNodeNext = outerNode->next;
			while (innerNodeNext)
			{
				if (outerNode->val == innerNodeNext->val)
				{
					if (!innerNodePrev)
					{
						innerNodePrev = outerNode;
					}
					innerNodePrev->next = innerNodeNext->next;
					delete innerNodeNext;
					innerNodeNext = innerNodePrev->next;
				}
				else
				{
					innerNodePrev = innerNodeNext;
					innerNodeNext = innerNodeNext->next;
				}
			}
			outerNode = outerNode->next;
		}

		return head;
	}
};

void test_Ch_2_1()
{
	Solution_2_1 sol;

	//ListNode *head = createList({ 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7});
	ListNode *head = createList({ 1, 1 });

	cout << "Printing original list : ";
	PrintList(head);

	head = sol.removeDuplicateWithoutUsingExtraSpace(head);
	cout << "Printing modified list : ";
	PrintList(head);
}

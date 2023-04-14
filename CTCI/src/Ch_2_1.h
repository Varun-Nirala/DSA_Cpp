#pragma once
/*
	Remove Duplicates :	Given a list head, remove duplicate elements
						1. With using extra space
						2. Without using extra space
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
}ListNode;

ListNode* createList(const vector<int> &v)
{
	if (v.empty())
		return nullptr;
	ListNode *head = new ListNode(v[0]);
	ListNode *p = head;

	for (int i = 1; i < v.size(); ++i)
	{
		p->next = new ListNode(v[i]);
		p = p->next;
	}
	return head;
}

void PrintList(ListNode *head)
{
	while (head)
	{
		cout << head->val << "->";
		head = head->next;
	}
	cout << "NULL\n";
}

class Solution {
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

int main()
{
	Solution sol;

	//ListNode *head = createList({ 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7});
	ListNode *head = createList({ 1, 1 });

	cout << "Printing original list : ";
	PrintList(head);

	head = sol.removeDuplicateWithoutUsingExtraSpace(head);
	cout << "Printing modified list : ";
	PrintList(head);

	return 0;
}

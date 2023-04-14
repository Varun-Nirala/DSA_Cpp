#pragma once

/*
	kth Element :	Given a list head, return kth from last elements
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

int main()
{
	Solution sol;

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

	return 0;
}

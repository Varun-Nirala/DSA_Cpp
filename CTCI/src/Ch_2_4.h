#pragma once

/*
	Partitiom :		Given a list and a val X, partition that list around X, such that all nodes
					less than X come before all node greater than or equal to X.
					if X is contained within the list, the values of X only need to be after the element
					less than X.
					Example :
						I/P : 3 -> 5 -> 8 -> 10 -> 2 -> 3 -> 1 [parition on 5]
						O/P : 3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8 [parition on 5]
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

ListNode* getkthElement(ListNode *head, int k)
{
	while (k--)
	{
		head = head->next;
	}
	return head;
}

class Solution {
public:
	ListNode* partition(ListNode *head, int val)
	{
		if (!head || !head->next)
			return head;
		ListNode *lessHead = nullptr;
		ListNode *greaterHead = nullptr;

		ListNode *lp = nullptr;
		ListNode *rp = nullptr;

		while (head)
		{
			if (head->val >= val)
			{
				if (!greaterHead)
				{
					greaterHead = head;
					rp = head;
				}
				else
				{
					rp->next = head;
					rp = rp->next;
				}
				if (lp && lp->next)
				{
					lp->next = lp->next->next;
				}
			}
			else
			{
				if (!lessHead)
				{
					lessHead = head;
					lp = head;
				}
				else
				{
					lp = lp->next;
				}
			}
			head = head->next;
		}
		rp->next = nullptr;

		lp->next = greaterHead;

		return lessHead ? lessHead : greaterHead;
	}
};

int main()
{
	Solution sol;
	vector<int> vec({ 3, 5, 8, 5, 10, 2, 1 });

	ListNode *head = createList(vec);

	cout << "Printing original list : ";
	PrintList(head);

	int val = 5;
	cout << "Partitioning it on val = " << val << endl;

	head = sol.partition(head, 5);

	cout << "Printing modified list : ";
	PrintList(head);

	return 0;
}

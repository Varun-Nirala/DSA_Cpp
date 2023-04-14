#pragma once

/*
	Delete middle Node :		Given only node which needed to be delete, delete that node,
							NOTE :: it will be mid one , any node other than first and last
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
	void removeGivenMidNode(ListNode *node)
	{
		ListNode *nodeToDel = node->next;
		node->val = nodeToDel->val;
		node->next = nodeToDel->next;
		delete nodeToDel;
	}
};

int main()
{
	Solution sol;
	vector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 });

	int k = vec.size() / 2;
	ListNode *head = createList(vec);

	ListNode *midElement = getkthElement(head, k);

	cout << "Printing original list : ";
	PrintList(head);

	cout << "Removing Node number : " << k << ", With val = " << midElement->val << endl;
	sol.removeGivenMidNode(midElement);

	cout << "Printing modified list : ";
	PrintList(head);

	return 0;
}

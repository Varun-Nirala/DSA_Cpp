#pragma once
/*
	Palindrome : Check if List is palindrome
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
	cout << "->NULL\n";
}

class Solution {
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

int main()
{
	Solution sol;
	vector<int> vec1({ 1, 2, 3, 2, 1 });
	vector<int> vec2({ 1, 2, 3, 3, 2, 1 });

	ListNode *head = createList(vec1);
	PrintList(head);

	cout << boolalpha << sol.isPalindrome(head) << endl;

	head = createList(vec2);
	PrintList(head);
	cout << boolalpha << sol.isPalindrome(head) << endl;

	return 0;
}

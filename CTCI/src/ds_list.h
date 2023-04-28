#pragma once

#include <vector>
#include <iostream>

struct ListNode
{
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* createList(const std::vector<int>& v)
{
	if (v.empty())
		return nullptr;
	ListNode* head = new ListNode(v[0]);
	ListNode* p = head;

	for (int i = 1; i < v.size(); ++i)
	{
		p->next = new ListNode(v[i]);
		p = p->next;
	}
	return head;
}

ListNode* getkthElement(ListNode* head, int k)
{
	while (k--)
	{
		head = head->next;
	}
	return head;
}

void PrintList(ListNode* head)
{
	while (head)
	{
		std::cout << head->val << "->";
		head = head->next;
	}
	std::cout << "NULL\n";
}

void PrintList(ListNode* head, vector<int> &vec)
{
	vec.clear();
	while (head)
	{
		vec.push_back(head->val);
		cout << head->val << "->";
		head = head->next;
	}
}
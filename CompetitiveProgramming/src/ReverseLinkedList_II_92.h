#ifndef __REVERSE_LINKLIST_II_92_H__
#define __REVERSE_LINKLIST_II_92_H__

#include <iostream>
#include <vector>
#include <string>
#include <stack>

#include "helper.h"

namespace nsCP
{
class Solution92
{
public:
	void test()
	{
		printf("Test : Solution92 -> Reverse Link List II : START\n");
		int m = 2;
		int n = 4;
		ListNode<int>* head = createList({ 1,2,3,4,5 });
		print(head, "Original List :: ");

		ListNode<int>* newHead = reverseBetween(head, m, n);
		print(newHead, "Reversed between " + std::to_string(m) + " and " + std::to_string(n));

		printf("Test : Solution92 -> Reverse Link List II : END\n\n");
	}
private:
	template <typename T>
	ListNode<T>* reverseBetween(ListNode<T>* head, int m, int n)
	{
		ListNode<T> *sHead = head;
		std::stack<T> ss;

		for (int i = 1; i < m; ++i)
		{
			head = head->next;
		}

		ListNode<T> *p = head;
		for (int i = m; i <= n; ++i)
		{
			ss.push(p->val);
			p = p->next;
		}

		head->val = ss.top();
		ss.pop();

		while (!ss.empty())
		{
			head->next = new ListNode<T>(ss.top());
			ss.pop();
			head = head->next;
		}
		head->next = p;
		return sHead;
	}
};
}
#endif //#ifndef __REVERSE_LINKLIST_II_92_H__

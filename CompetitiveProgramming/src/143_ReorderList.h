#ifndef __143_REORDER_LINKLIST_H__
#define __143_REORDER_LINKLIST_H__

#include <iostream>
#include <vector>
#include <string>
#include <stack>

#include "helper.h"

namespace nsCP
{
class Solution143
{
public:
	//Given      L : L0 -> L1 ->L2 -> ... -> Ln-1 ->Ln
	//Reorder L To : L0 -> Ln ->L1 -> Ln-1 -> L2 -> Ln-2 ->...
	void test()
	{
		printf("Test : Solution143 -> Reorder Link List : START\n");
		//Given 1->2->3->4, reorder it to 1->4->2->3.
		//Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
		ListNode<int>* inList = createList({ 1, 2, 3, 4 });
		print(inList, "Original Lists :: ");
		reorderList(inList);
		print(inList, "Output Lists :: ");

		inList = createList({ 1,2,3,4,5 });
		print(inList, "Original Lists :: ");
		reorderList(inList);
		print(inList, "Output Lists :: ");

		printf("Test : Solution143 -> Reorder Link List : END\n\n");
	}
public:
	template <typename T>
	void reorderList(ListNode<T>* head)
	{
		std::stack<ListNode<T> *> ss;

		ListNode<T> *p = head;
		while (p)
		{
			ss.push(p);
			p = p->next;
		}

		//Given 1->2->3->4,		reorder it to 1->4->2->3.
		//Given 1->2->3->4->5,	reorder it to 1->5->2->4->3.

		size_t max = ss.size() / 2;
		if ((ss.size() % 2))
		{
			max++;
		}

		p = head;
		for (size_t i = 0; i < max; ++i)
		{
			ListNode<T>* nextNext = p->next;
			p->next = ss.top();
			ss.pop();
			p = p->next;
			if (i != max - 1)
			{
				p->next = nextNext;
				p = p->next;
			}
			else
			{
				p->next = nullptr;
			}
		}
	}
};
}
#endif //#ifndef __143_REORDER_LINKLIST_H__
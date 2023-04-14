#ifndef __ODD_EVEN_LINKLIST_328_H__
#define __ODD_EVEN_LINKLIST_328_H__

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include "helper.h"

using namespace std;

namespace nsCP
{
class Solution328
{
public:
	void test()
	{
		printf("Test : Solution328 -> Odd Even Link List : START\n");
		// Input  : 1->2->3->4->5->NULL
		// Output : 1->3->5->2->4->NULL
		ListNode<int>* list = createList({ 1,2,3,4,5 });
		print(list, "Original Lists :: ");
		list = oddEvenList(list);
		print(list, "Output Lists :: ");

		// Input  : 2->1->3->5->6->4->7->NULL
		// Output : 2->3->6->7->1->5->4->NULL
		list = createList({ 2,1,3,5,6,4,7 });
		print(list, "Original Lists :: ");
		list = oddEvenList(list);
		print(list, "Output Lists :: ");

		// Input  : 1->2->3->4->5->6->7->8->NULL
		// Output : 1->3->5->7->2->4->6->8->NULL
		list = createList({ 1,2,3,4,5,6,7,8 });
		print(list, "Original Lists :: ");
		list = oddEvenList(list);
		print(list, "Output Lists :: ");

		printf("Test : Solution328 -> Odd Even Link List : END\n\n");
	}

private:
	template <typename T>
	ListNode<T>* oddEvenList(ListNode<T>* head)
	{
		if (!head || (head && !(head->next)))
			return head;

		ListNode<T>* evenStart{ nullptr };
		ListNode<T> *p = head;

		int size = 0;
		while (p->next)
		{
			p = p->next;
			size++;
		}
		size++;
		evenStart = p;      // This is end node

		size = size / 2;
		p = head;
		while (size--)
		{
			evenStart->next = p->next;
			evenStart = evenStart->next;
			p->next = evenStart->next;
			p = p->next;
		}
		evenStart->next = nullptr;
		return head;
	}
};
}
#endif //#ifndef __ODD_EVEN_LINKLIST_328_H__
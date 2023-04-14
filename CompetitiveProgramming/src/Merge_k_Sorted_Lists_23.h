#ifndef __MERGE_K_SORTED_LIST_23_H__
#define __MERGE_K_SORTED_LIST_23_H__

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include "helper.h"

namespace nsCP
{
class Solution23
{
public:
	void test()
	{
		printf("Test : Solution23   -> Merge K Sorted Lists : START\n");
		int m = 2;
		int n = 4;

		std::vector<ListNode<int>*> vec;
		vec.push_back(createList({ 1, 4, 5 }));
		vec.push_back(createList({ 1, 3, 4 }));
		vec.push_back(createList({ 2, 6 }));

		std::cout << "Original Lists :: ";
		for (size_t i = 0; i < vec.size(); ++i)
		{
			print(vec[i], "List # " + std::to_string(i + 1));
		}

		ListNode<int>* newHead = mergeKLists(vec);
		print(newHead, "Output merged List ");

		printf("Test : Solution23   -> Merge K Sorted Lists : END\n\n");
	}

private:
	template<typename T>
	ListNode<T>* mergeKLists(std::vector<ListNode<T>*>& lists)
	{
		ListNode<T>* outputList{ nullptr };

		auto cmp = [](const ListNode<T> *l1, const ListNode<T> *l2) {
			return l1->val > l2->val;
		};

		std::priority_queue<ListNode<T> *, std::vector<ListNode<T> *>, decltype(cmp)> que(cmp);

		for (auto &x : lists)
		{
			if (x)
			{
				que.push(x);
			}
		}

		if (que.empty())
		{
			return nullptr;
		}

		ListNode<T> *f = que.top();
		que.pop();

		if (f->next)
		{
			que.push(f->next);
		}

		outputList = new ListNode<T>(f->val);

		ListNode<T> *p = outputList;

		while (!que.empty())
		{
			ListNode<T> *curr = que.top();
			que.pop();

			p->next = new ListNode<T>(curr->val);
			p = p->next;

			if (curr->next)
			{
				que.push(curr->next);
			}
		}
		return outputList;
	}
};
}
#endif //__MERGE_K_SORTED_LIST_23_H__
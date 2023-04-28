#pragma once

/*
	Delete middle Node :		Given only node which needed to be delete, delete that node,
							NOTE :: it will be mid one , any node other than first and last
*/

#include <iostream>
#include <vector>

#include <set>

#include "ds_list.h"

using namespace std;

class Solution_2_3
{
public:
	void removeGivenMidNode(ListNode *node)
	{
		ListNode *nodeToDel = node->next;
		node->val = nodeToDel->val;
		node->next = nodeToDel->next;
		delete nodeToDel;
	}
};

void test_Ch_2_3()
{
	Solution_2_3 sol;
	vector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 });

	int k = (int)vec.size() / 2;
	ListNode *head = createList(vec);

	ListNode *midElement = getkthElement(head, k);

	cout << "Printing original list : ";
	PrintList(head);

	cout << "Removing Node number : " << k << ", With val = " << midElement->val << endl;
	sol.removeGivenMidNode(midElement);

	cout << "Printing modified list : ";
	PrintList(head);
}

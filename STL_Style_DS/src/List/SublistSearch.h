#pragma once
#include <iostream>

using namespace std;

namespace Searching_2
{
	// Problem Statement :: Given two linked lists, the task is to check whether the first list is present in 2nd list or not.
	typedef struct Node
	{
		int data;
		Node *next;
	}Node;

	Node *newNode(int val)
	{
		Node* newNode = new Node();
		newNode->data = val;
		newNode->next = NULL;
		return newNode;
	}

	void PrintList(Node *node)
	{
		while (node)
		{
			cout << node->data << ", " << endl;
			node = node->next;
		}
	}

	// Problem Statement :: Given two linked lists, the task is to check whether the first list is present in 2nd list or not.
	bool findList(Node *first, Node *second)
	{
		if (first == NULL && second == NULL)
		{
			return true;
		}

		if (first == NULL || second == NULL)
		{
			return false;
		}

		Node *ptr1 = first;
		Node *ptr2 = second;

		while (ptr1 && ptr2)
		{
			if (ptr1->data == ptr2->data)
			{
				ptr1 = ptr1->next;
				ptr2 = ptr2->next;
			}
			else
			{
				break;
			}
		}

		if (ptr1 != NULL && ptr2 == NULL)
		{
			return false;
		}

		if (!ptr1)
		{
			return true;
		}

		return findList(first, second->next);
	}

	/* Driver program to test above functions*/
	int main(int argc, char *argv[])
	{
		/* Let us create two linked lists to test
		the above functions. Created lists shall be
		a: 1->2->3->4
		b: 1->2->1->2->3->4*/
		Node *a = newNode(1);
		a->next = newNode(2);
		a->next->next = newNode(3);
		a->next->next->next = newNode(4);

		Node *b = newNode(1);
		b->next = newNode(2);
		b->next->next = newNode(1);
		b->next->next->next = newNode(2);
		b->next->next->next->next = newNode(3);
		b->next->next->next->next->next = newNode(4);

		findList(a, b) ? cout << "LIST FOUND" :
			cout << "LIST NOT FOUND";

		return 0;
	}
}
#pragma once

/*
	Sum Two List : Given two list with Least Significant Digit at left, add and return a new list.
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

vector<int> PrintList(ListNode *head)
{
	vector<int> vec;
	while (head)
	{
		vec.push_back(head->val);
		cout << head->val << "->";
		head = head->next;
	}
	return vec;
}

int getNumber(vector<int> &vec)
{
	int ans = 0;
	int mult = vec.size() - 1;
	for (auto x : vec)
	{
		ans += x * pow(10, mult--);
	}
	return ans;
}

class Solution {
	void print(ListNode *h1, bool inRev)
	{
		vector<int> vec;
		vec = PrintList(h1);
		if (inRev)
			reverse(vec.begin(), vec.end());
		cout << "\t Number = " << getNumber(vec) << endl;;
	}

	void addUp(int v1, int v2, int &sum, int &carry)
	{
		sum = carry + v1 + v2;
		if (sum > 9)
		{
			carry = sum / 10;
			sum = sum % 10;
		}
		else
		{
			carry = 0;
		}
	}

	void addUp(int v1, int v2, int &sum, int &carry, ListNode *p)
	{
		sum = carry + v1 + v2;
		if (sum > 9)
		{
			carry = sum / 10;
			sum = sum % 10;
		}
		else
		{
			carry = 0;
		}
		p->next = new ListNode(sum);
		p = p->next;
	}

	ListNode *sumLeastIterative(ListNode *h1, ListNode *h2)
	{
		if (!h1)
			return h2;

		if (!h2)
			return h1;

		print(h1, true);
		print(h2, true);

		int carry = 0, sum = 0;

		addUp(h1->val, h2->val, sum, carry);

		h1 = h1->next;
		h2 = h2->next;

		ListNode *head = new ListNode(sum);
		ListNode *p = head;

		while (h1 && h2)
		{
			addUp(h1->val, h2->val, sum, carry, p);
			h1 = h1->next;
			h2 = h2->next;
		}

		while (h1)
		{
			addUp(h1->val, 0, sum, carry, p);
			h1 = h1->next;
		}

		while (h2)
		{
			addUp(0, h2->val, sum, carry, p);
			h2 = h2->next;
		}

		if (carry)
		{
			p->next = new ListNode(carry);
		}

		print(head, true);

		return head;
	}

	ListNode* sumLeastRecursiveUtil(ListNode *h1, ListNode *h2, int carry)
	{
		if (!h1 && !h2 && !carry)
			return nullptr;

		ListNode *node = nullptr;
		int sum = 0;

		if (h1 && h2)
		{
			addUp(h1->val, h2->val, sum, carry);
		}
		else if (h1)
		{
			addUp(h1->val, 0, sum, carry);
		}
		else if (h2)
		{
			addUp(0, h2->val, sum, carry);
		}

		if (h1 || h2)
		{
			node = new ListNode(sum);
		}
		else
		{
			node = new ListNode(carry);
			carry = 0;
		}
		node->next = sumLeastRecursiveUtil(h1 ? h1->next : nullptr, h2 ? h2->next : nullptr, carry);
		return node;
	}

	ListNode* sumLeastRecursive(ListNode *h1, ListNode *h2)
	{
		if (!h1)
			return h2;

		if (!h2)
			return h1;

		print(h1, true);
		print(h2, true);

		return sumLeastRecursiveUtil(h1, h2, 0);
	}
public:
	ListNode* sumListLeastSignificantFirst(ListNode *h1, ListNode *h2, bool bCallRecursive)
	{
		ListNode *head = nullptr;
		if (bCallRecursive)
		{
			head = sumLeastRecursive(h1, h2);
		}
		else
		{
			head = sumLeastIterative(h1, h2);
		}

		cout << "Prinitng Sum List :\n";
		print(head, true);
		return head;
	}
};

int main()
{
	Solution sol;
	vector<int> vec1({ 7, 1, 6 });
	vector<int> vec2({ 5, 9, 4 });

	ListNode *h1 = createList(vec1);
	ListNode *h2 = createList(vec2);

	sol.sumListLeastSignificantFirst(h1, h2, true);

	//sol.sumListMostSignificantFirst(h1, h2);

	return 0;
}

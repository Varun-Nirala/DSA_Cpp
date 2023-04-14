#ifndef __707_DESIGN_LINKLIST_H__
#define __707_DESIGN_LINKLIST_H__

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include "helper.h"

namespace nsCP
{
template <typename T>
class MyLinkedList
{
public:
	/** Initialize your data structure here. */
	MyLinkedList() = default;
	~MyLinkedList() { clear(); }

	inline size_t size() const { return m_size; }
	inline bool empty() const { return m_size == 0; }

	const T& front() const;
	T& front();

	const T& back() const;
	T& back();

	inline void clear();

	/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
	inline T get(size_t index) const;

	/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
	inline void push_front(T val);

	/** Append a node of value val to the last element of the linked list. */
	inline void push_back(T val);

	/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
	inline void insert(size_t index, T val);

	/** Delete the index-th node in the linked list, if the index is valid. */
	inline void erase(size_t index);

	inline void pop_back();

	inline void pop_front();

	ListNode<T>* getHead() { return m_pHead; }
	ListNode<T>* getTail() { return m_pTail; }
private:
	ListNode<T>		*m_pHead{};
	ListNode<T>		*m_pTail{};
	size_t			m_size{};
};

template<typename T>
const T& MyLinkedList<T>::front() const
{
	return m_pHead->val;
}

template<typename T>
T& MyLinkedList<T>::front()
{
	return m_pHead->val;
}

template<typename T>
const T& MyLinkedList<T>::back() const
{
	return m_pTail->val;
}

template<typename T>
T& MyLinkedList<T>::back()
{
	return m_pTail->val;
}

template<typename T>
void MyLinkedList<T>::clear()
{
	ListNode<T>* p = m_pHead;
	while (p)
	{
		ListNode<T>* del = p;
		p = p->next;
		delete del;
	}
}

/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
template<typename T>
T MyLinkedList<T>::get(size_t index) const
{
	if (index >= m_size)
	{
		return -1;
	}
	ListNode<T>* p = m_pHead;
	while (index--)
	{
		p = p->next;
	}
	return p->val;
}

/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
template<typename T>
void MyLinkedList<T>::push_front(T val)
{
	if (m_size)
	{
		ListNode<T>* node = new ListNode<T>(val);
		node->next = m_pHead;
		m_pHead = node;
	}
	else
	{
		m_pTail = m_pHead = new ListNode<T>(val);
	}
	m_size++;
}

/** Append a node of value val to the last element of the linked list. */
template<typename T>
void MyLinkedList<T>::push_back(T val)
{
	if (m_size)
	{
		ListNode<T>* node = new ListNode<T>(val);
		m_pTail->next = node;
		m_pTail = node;
	}
	else
	{
		m_pTail = m_pHead = new ListNode<T>(val);
	}
	m_size++;
}

/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
template<typename T>
void MyLinkedList<T>::insert(size_t index, T val)
{
	if (index == 0)
	{
		push_front(val);
	}
	else if (index == m_size)
	{
		push_back(val);
	}
	else if (index > 0 && index < m_size)
	{
		ListNode<T>* p = m_pHead;
		while (--index)
		{
			p = p->next;
		}
		ListNode<T>* nn = p->next;
		p->next = new ListNode<T>(val);
		p = p->next;
		p->next = nn;
		m_size++;
	}
}

/** Delete the index-th node in the linked list, if the index is valid. */
template<typename T>
void MyLinkedList<T>::erase(size_t index)
{
	if (index == 0)
	{
		pop_front();
	}
	else if (index == m_size - 1)
	{
		pop_back();
	}
	else if (index > 0 && index < m_size)
	{
		ListNode<T>* p = m_pHead;
		while (--index)
		{
			p = p->next;
		}
		ListNode<T>* nn = p->next;
		p->next = nn->next;
		delete nn;
		m_size--;
	}
}

template<typename T>
void MyLinkedList<T>::pop_back()
{
	if (m_size > 1)
	{
		ListNode<T>* p = m_pHead;
		while (p->next != m_pTail)
		{
			p = p->next;
		}
		delete (p->next);
		m_pTail = p;
		p->next = nullptr;
		m_size--;
	}
	else if (m_size == 1)
	{
		delete m_pHead;
		m_pHead = m_pTail = nullptr;
		m_size = 0;
	}
}

template<typename T>
void MyLinkedList<T>::pop_front()
{
	if (m_size > 1)
	{
		ListNode<T>* p = m_pHead->next;
		delete m_pHead;
		m_pHead = p;
		m_size--;
	}
	else if (m_size == 1)
	{
		delete m_pHead;
		m_pHead = m_pTail = nullptr;
		m_size = 0;
	}
}

class Solution707
{
public:
	void test()
	{
		printf("Test : Solution707 -> Design List : START\n");
		MyLinkedList<int> ll;
		ll.push_front(2);
		ll.push_front(1);
		ll.push_back(3);
		ll.push_back(4);

		print(ll.getHead());

		ll.insert(0, 10);
		ll.insert(ll.size(), 11);

		print(ll.getHead());

		ll.erase(0);
		ll.erase(ll.size() - 1);

		print(ll.getHead());
		printf("Test : Solution707 -> Design List : END\n\n");
	}
};
}
#endif //#ifndef __707_DESIGN_LINKLIST_H__

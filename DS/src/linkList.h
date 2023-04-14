#pragma once

#include <iostream>

#include "Common/helper.h"
#include "Common/logger.h"

template <typename T>
class LinkList
{
public:
	using dataType = T;

private:
	struct Node
	{
		Node		*m_pNext{};
		dataType	m_data{};

		Node() = default;

		explicit Node(dataType val)
			: m_data(val)
		{}
	};

public:
	LinkList() = default;
	~LinkList() { clear(); }

	void clear()
	{
		while (!empty())
		{
			pop_front();
		}
	}

	size_t size() const { return m_size; }
	bool empty() const { return m_size == 0; }

	const dataType& front() const
	{
		ASSERT(!empty());
		return m_pHead->m_data;
	}

	const dataType& back() const
	{
		ASSERT(!empty());
		return m_pHead->m_data;
	}

	dataType& front()
	{
		ASSERT(!empty());
		return m_pHead->m_data;
	}

	dataType& back()
	{
		ASSERT(!empty());
		return m_pHead->m_data;
	}

	void push_back(dataType value)
	{
		Node* newNode = new Node(value);
		if (!m_pHead)
		{
			m_pHead = m_pTail = newNode;
		}
		else
		{
			m_pTail->m_pNext = newNode;
			m_pTail = newNode;
		}
		m_size++;
	}

	void push_front(dataType value)
	{
		Node* newNode = new Node(value);
		if (!m_pHead)
		{
			m_pHead = m_pTail = newNode;
		}
		else
		{
			newNode->m_pNext = m_pHead;
			m_pHead = newNode;
		}
		m_size++;
	}

	void pop_front()
	{
		ASSERT(!empty());
		if (!empty())
		{
			Node* next = m_pHead->m_pNext;
			delete m_pHead;
			m_pHead = next;
			m_size--;
			if (m_size == 0)
			{
				m_pTail = nullptr;
			}
		}
	}

	// new node should be at pos position
	void insert(size_t pos, dataType value)
	{
		if (pos <= m_size)
		{
			if (pos == 0)
			{
				push_front(value);
			}
			else if (pos == m_size)
			{
				push_back(value);
			}
			else
			{
				Node* curr = m_pHead;
				while (--pos)
				{
					curr = curr->m_pNext;
				}
				Node* newNode = new Node(value);
				newNode->m_pNext = curr->m_pNext;
				curr->m_pNext = newNode;
				m_size++;
			}
		}
	}

	// erase node pos position
	void erase(size_t pos)
	{
		ASSERT(!empty());
		if (pos <= m_size)
		{
			if (pos == 0)
			{
				pop_front();
			}
			else
			{
				Node* curr = m_pHead;
				while (--pos)
				{
					curr = curr->m_pNext;
				}
				Node* next = curr->m_pNext;
				curr->m_pNext = curr->m_pNext->m_pNext;
				delete next;
				m_size--;
			}
		}
	}

	void print() const
	{
		if (empty())
		{
			ns_Util::Logger::LOG_MSG("List empty!\n");
		}
		else
		{
			Node* curr = m_pHead;
			ns_Util::Logger::LOG_MSG("List Size : ", m_size, '\n');
			while (curr)
			{
				ns_Util::Logger::LOG_MSG(curr->m_data, " -> ");
				curr = curr->m_pNext;
			}
			ns_Util::Logger::LOG_MSG(" nullptr\n");
		}
	}

private:
	Node	*m_pHead{};
	Node	*m_pTail{};
	size_t	m_size{};
};
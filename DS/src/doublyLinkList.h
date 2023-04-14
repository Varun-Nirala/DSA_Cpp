#pragma once

#include <iostream>

#include "Common/helper.h"
#include "Common/logger.h"

template <typename T>
class DoublyLinkList
{
public:
	using dataType = T;

private:
	struct Node
	{
		Node		*m_pLeft{};
		Node		*m_pRight{};
		dataType	m_data{};

		Node() = default;

		explicit Node(dataType val)
			: m_data(val)
		{}
	};
public:
	DoublyLinkList() = default;
	~DoublyLinkList() { clear(); }

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
		return m_pTail->m_data;
	}

	dataType& front()
	{
		ASSERT(!empty());
		return m_pHead->m_data;
	}

	dataType& back()
	{
		ASSERT(!empty());
		return m_pTail->m_data;
	}

	void push_back(dataType value)
	{
		Node* newNode = new Node(value);
		if (!m_pTail)
		{
			m_pHead = m_pTail = newNode;
		}
		else
		{
			m_pTail->m_pRight = newNode;
			newNode->m_pLeft = m_pTail;
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
			newNode->m_pRight = m_pHead;
			m_pHead->m_pLeft = newNode;
			m_pHead = newNode;
		}
		m_size++;
	}

	void pop_back()
	{
		ASSERT(!empty());
		if (!empty())
		{
			Node* left = m_pTail->m_pLeft;
			delete m_pTail;
			m_pTail = left;

			if (m_pTail)
			{
				m_pTail->m_pRight = nullptr;
			}

			m_size--;
			if (m_size == 0)
			{
				m_pTail = m_pHead = nullptr;
			}
		}
	}

	void pop_front()
	{
		ASSERT(!empty());
		if (!empty())
		{
			Node* right = m_pHead->m_pRight;
			delete m_pHead;
			m_pHead = right;

			if (m_pHead)
			{
				m_pHead->m_pLeft = nullptr;
			}

			m_size--;
			if (m_size == 0)
			{
				m_pTail = m_pHead = nullptr;
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
					curr = curr->m_pRight;
				}
				Node* newNode = new Node(value);

				newNode->m_pRight = curr->m_pRight;
				newNode->m_pLeft = curr;

				curr->m_pRight = newNode;
				newNode->m_pRight->m_pLeft = newNode;

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
					curr = curr->m_pRight;
				}
				Node* right = curr->m_pRight;
				curr->m_pRight = right->m_pRight;
				right->m_pRight->m_pLeft = curr;

				delete right;
				m_size--;

				if (m_size == 0)
				{
					m_pHead = m_pTail = nullptr;
				}
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
				curr = curr->m_pRight;
			}
			ns_Util::Logger::LOG_MSG(" nullptr\n");
		}
	}

private:
	Node	*m_pHead{};
	Node	*m_pTail{};
	size_t	m_size{};
};
#pragma once

#include "LinkList.h"

template<typename T>
class Queue
{
	using dataType = typename LinkList<T>::dataType;
public:
	Queue() = default;
	~Queue() { clear(); }

	size_t size() const { return m_list.size(); }
	bool empty() const { return m_list.empty(); }

	void clear()
	{
		m_list.clear();
	}

	void push(dataType data)
	{
		m_list.push_back(data);
	}

	const dataType& front() const
	{
		ASSERT(!empty());
		return m_list.front();
	}

	dataType& front()
	{
		SSERT(!empty());
		return m_list.front();
	}

	const dataType& back() const
	{
		ASSERT(!empty());
		return m_list.back();
	}

	dataType& back()
	{
		ASSERT(!empty());
		return m_list.back();
	}

	void pop()
	{
		ASSERT(!empty());
		return m_list.pop_front()
	}

private:
	LinkList<dataType>	m_list;
};
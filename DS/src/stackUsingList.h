#pragma once

#include "linkList.h"

template <typename T>
class StackUsingList
{
	using dataType = typename LinkList<T>::dataType;
public:
	StackUsingList() = default;
	~StackUsingList() { clear(); }

	size_t size() const { return m_list.size(); }
	bool empty() const { return m_list.empty(); }

	void clear()
	{
		m_list.clear();
	}

	void push(dataType data)
	{
		m_list.push_front(data);
	}

	void pop()
	{
		ASSERT(!empty());
		m_list.pop_front();
	}

	const dataType& top() const
	{
		ASSERT(!empty());
		m_list.front();
	}

	dataType& top()
	{
		ASSERT(!empty());
		m_list.front();
	}

private:
	LinkList<dataType>		m_list;
};
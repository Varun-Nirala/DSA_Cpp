#pragma once

#include "doublyLinkList.h"

template <typename T>
class DequeueUsingList
{
	using dataType = typename DoublyLinkList<T>::dataType;
public:
	DequeueUsingList() = default;
	~DequeueUsingList() { clear(); }

	size_t size() const { return m_list.size(); }
	bool empty() const { return m_list.empty(); }

	void clear()
	{
		m_list.clear();
	}

	void push_front(dataType data)
	{
		m_list.push_front(data);
	}

	void push_back(dataType data)
	{
		m_list.push_back(data);
	}

	void pop_front()
	{
		ASSERT(!empty());
		m_list.pop_front();
	}

	void pop_back()
	{
		ASSERT(!empty());
		m_list.pop_back();
	}

	const dataType& front() const
	{
		ASSERT(!empty());
		return m_list.front();
	}

	const dataType& back() const
	{
		ASSERT(!empty());
		return m_list.back();
	}

	dataType& front()
	{
		ASSERT(!empty());
		return m_list.front();
	}

	dataType& back()
	{
		ASSERT(!empty());
		return m_list.back();
	}

private:
	DoublyLinkList<dataType>		m_list;
};
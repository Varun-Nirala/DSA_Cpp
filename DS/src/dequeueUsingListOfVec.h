#pragma once

#include "doublyLinkList.h"

#include <list>
#include <array>

template <typename T>
class DequeueUsingListOfVec
{
	using dataType = T;
public:
	DequeueUsingListOfVec() = default;
	~DequeueUsingListOfVec() { clear(); }

	size_t size() const { return m_size; }
	bool empty() const { return m_list.empty(); }

	void clear()
	{
		m_list.clear();
	}

	void push_front(dataType data)
	{
		if (m_frontIndex == 0)
		{
			m_list.push_front({});
			m_frontIndex = m_bucketSize - 1;
		}
		m_list.front()[m_frontIndex--] = data;
		m_size++;
	}

	void push_back(dataType data)
	{
		if (m_backIndex == m_bucketSize)
		{
			m_list.push_back({});
			m_backIndex = 0;
		}
		m_list.back()[m_backIndex++] = data;
		m_size++;
	}

	void pop_front()
	{
		ASSERT(!empty());
		if (!empty())
		{
			if (m_frontIndex < m_bucketSize)
			{
				m_frontIndex++;
			}

			if (m_frontIndex == m_bucketSize)
			{
				m_list.pop_front();
				m_frontIndex = 0;
			}
			m_size--;
		}
	}

	void pop_back()
	{
		ASSERT(!empty());
		if (!empty())
		{
			if (m_backIndex >= 0)
			{
				m_backIndex--;
			}

			if (m_backIndex < 0)
			{
				m_list.pop_back();
				m_backIndex = m_bucketSize - 1;
			}
			m_size--;
		}
	}

	const dataType& front() const
	{
		ASSERT(!empty());
		if (!empty())
		{
			return m_list.front()[m_frontIndex];
		}
		return {};
	}

	const dataType& back() const
	{
		ASSERT(!empty());
		if (!empty())
		{
			return m_list.back()[m_backIndex];
		}
		return {};
	}

	dataType& front()
	{
		ASSERT(!empty());
		if (!empty())
		{
			return m_list.front()[m_frontIndex];
		}
		dataType temp;
		return temp;
	}

	dataType& back()
	{
		ASSERT(!empty());
		if (!empty())
		{
			return m_list.back()[m_backIndex];
		}
		dataType temp;
		return temp;
	}

private:
	constexpr static int							m_bucketSize{8};
	std::list<std::array<dataType, m_bucketSize>>	m_list;
	size_t											m_size{};
	int												m_frontIndex{m_bucketSize - 1};
	int												m_backIndex{};
};
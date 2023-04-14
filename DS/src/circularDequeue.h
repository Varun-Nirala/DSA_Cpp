#pragma once

#include <vector>
#include <iostream>

#include "Common/helper.h"
#include "Common/logger.h"

template <typename T>
class CircularDequeue
{
	using dataType = T;
public:
	~CircularDequeue() { clear(); }

	explicit CircularDequeue(size_t capacity)
	{
		m_vec.resize(capacity);
	}

	size_t capacity() const { return m_vec.size(); }
	bool empty() const { return size() == 0; }
	
	size_t size() const
	{
		if (m_front < m_back)
		{
			return m_front - m_back;
		}
		return m_back + (capacity() - m_front);
	}

	void clear()
	{
		m_vec.clear();
		m_front = m_back = 0;
	}

	void resize(size_t size)
	{
		m_vec.resize(size);
	}

	const dataType& front() const
	{
		ASSERT(!empty());
		return m_vec[m_front];
	}

	const dataType& back() const
	{
		ASSERT(!empty());
		return m_vec[m_back];
	}

	dataType& front()
	{
		ASSERT(!empty());
		return m_vec[m_front];
	}

	dataType& back()
	{
		ASSERT(!empty());
		return m_vec[m_back];
	}

	void push_front(const dataType& data)
	{
		if (size() == capacity())
		{
			ASSERT(!"Queue is full!");
			return;
		}
		if (m_front == 0)
		{
			m_front = capacity() - 1;
		}
		else
		{
			--m_front;
		}
		m_vec[m_front] = data;
	}

	void push_back(const dataType& data)
	{
		if (size() == capacity())
		{
			ASSERT(!"Queue is full!");
			return;
		}
		++m_back;
		if (m_back == capacity())
		{
			m_back = 0;
		}
		m_vec[m_back] = data;
	}

	void pop_front()
	{
		ASSERT(!empty());

		++m_front;

		if (m_front == m_back)
		{
			m_front = m_back = 0;
		}
		else if (m_front == capacity())
		{
			m_front = 0;
		}
	}

	void pop_back()
	{
		ASSERT(!empty());

		if (m_back > 0)
		{
			--m_back;
		}
		else
		{
			m_back = capacity() - 1;
		}
	}

private:
	std::vector<dataType>	m_vec;
	size_t					m_front{};
	size_t					m_back{};
};
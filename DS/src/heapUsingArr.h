#pragma once

#include <vector>
#include <functional>

#include "Common/helper.h"
#include "Common/logger.h"

template<typename T>
class MaxHeapUsingArr
{
	using dataType = T;
public:
	explicit MaxHeapUsingArr(size_t capacity, std::function<bool(const dataType &, const dataType&)> comparator = std::less<dataType>())
		: m_compareFunc(comparator)
	{
		m_vec.resize(capacity);
	}

	~MaxHeapUsingArr() { clear(); }

	size_t size() const { return m_size; }
	size_t capacity() const { return m_vec.size(); }
	bool empty() const { return size() == 0; }

	// makes capacity 0
	void clear()
	{
		m_vec.clear();
		m_size = 0;
	}

	void resize(size_t size)
	{
		m_vec.resize(size);
	}

	void push(const dataType& key)
	{
		if (capacity() == size())
		{
			m_vec.push_back(key);
			++m_size;
		}
		else
		{
			m_vec[m_size++] = key;
		}
		swimUp(m_size - 1);
	}

	void pop()
	{
		ASSERT(!empty());
		std::swap(m_vec[0], m_vec[m_size - 1]);
		--m_size;
		sinkDown(0);
	}

	const dataType& top() const
	{
		ASSERT(!empty());
		return m_vec[0];
	}

	dataType& top()
	{
		ASSERT(!empty());
		return m_vec[0];
	}

private:
	// Zero base index
	inline size_t parent(size_t index)
	{
		return (index - 1) / 2;
	}

	inline size_t left(size_t index)
	{
		return (2 * index) + 1;
	}

	inline size_t right(size_t index)
	{
		return (2 * index) + 2;
	}

	void swimUp(size_t index)
	{
		size_t parent = parent(index);

		if (parent && m_compareFunc(m_vec[index], m_vec[parent]))
		{
			std::swap(m_vec[parent], m_vec[index]);

			swimUp(parent);
		}
	}

	void sinkDown(size_t index)
	{
		size_t left = left(index);
		size_t right = right(index);

		size_t maxID{};
		if (left < m_size && m_compareFunc(m_vec[index], m_vec[left]);
		{
			maxID = left;
		}

		if (right < m_size && m_compareFunc(m_vec[maxID], m_vec[right]);
		{
			maxID = right;
		}

		if (maxID != index)
		{
			std::swap(m_vec[maxId], m_vec[index]);
			sinkDown(maxId);
		}
	}

private:
	std::vector<dataType>											m_vec;
	size_t															m_size{};
	const std::function<bool(const dataType&, const dataType&)>		m_compareFunc;
};
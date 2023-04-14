#pragma once

#include "Common/logger.h"
#include "Common/helper.h"

#include <utility>

template<typename T>
class DynamicArr
{
	using dataType = T;
public:
	~DynamicArr() { clear(); }

	void clear()
	{
		delete[] m_pArr;
		m_pArr = nullptr;
		m_size = m_capacity = 0;
	}

	DynamicArr() = default;

	explicit DynamicArr(size_t size, const dataType& val = dataType())
	{
		m_pArr = new dataType[size](val);
		m_size = m_capacity = size;
	}

	size_t size() const { return m_size; }
	size_t capacity() const { return m_capacity; }
	bool empty() const { return m_size == 0; }

	void resize(size_t capacity)
	{
		dataType* newArr = new dataType[capacity]{ dataType() };
		
		std::move(m_pArr, m_pArr + std::min(capacity, m_capacity), newArr);
		delete[] m_pArr;
		m_pArr = newArr;
		m_size = m_capacity = capacity;
	}

	void insert(size_t pos, const dataType& val)
	{
		if (m_size == m_capacity)
		{
			dataType* newArr = new dataType[m_capacity * 2];
			std::move(m_pArr, m_pArr + pos, newArr);

			std::move(m_pArr + pos + 1, m_pArr + m_capacity, newArr + pos + 1);

			delete[] m_pArr;
			m_pArr = newArr;

			m_capacity = m_capacity * 2;
		}
		else
		{
			makeSpaceFor(m_pArr, pos, 1);
		}
		m_pArr[pos] = val;
		++m_size;
	}

	void insert(size_t pos, dataType&& val)
	{
		if (m_size == m_capacity)
		{
			dataType* newArr = new dataType[m_capacity * 2];
			std::move(m_pArr, m_pArr + pos, newArr);

			std::move(m_pArr + pos + 1, m_pArr + m_capacity, newArr + pos + 1);

			delete[] m_pArr;
			m_pArr = newArr;

			m_capacity = m_capacity * 2;
		}
		else
		{
			makeSpaceFor(m_pArr, pos, 1);
		}
		m_pArr[pos] = std::move(val);
		++m_size;
	}

	void insert(size_t pos, size_t count, const dataType& val)
	{
		if (m_size + count >= m_capacity)
		{
			int multiplier = 2;
			while (m_size + count <= m_capacity * multiplier)
			{
				++multiplier;
			}

			dataType* newArr = new dataType[m_capacity * multiplier];
			std::move(m_pArr, m_pArr + pos, newArr);

			std::move(m_pArr + pos + 1, m_pArr + m_capacity, newArr + pos + count);

			delete[] m_pArr;
			m_pArr = newArr;

			m_capacity = m_capacity * multiplier;
		}
		else
		{
			makeSpaceFor(m_pArr, pos, count);
		}

		for (Size_t i = 0; i < count; ++i)
		{
			m_pArr[pos++] = val;
		}
	}

	void reserve(size_t capacity)
	{
		if (capacity > m_capacity)
		{
			dataType* newArr = new dataType[capacity];

			std::move(m_pArr, m_pArr + m_size, newArr);

			delete[] m_pArr;
			m_pArr = newArr;
			m_capacity = capacity;
		}
	}

	void push_back(const dataType& val)
	{
		if (m_size == m_capacity)
		{
			reserve(m_capacity * 2);
		}

		m_pArr[m_size] = val;
		++m_size;
	}

	void push_back(dataType&& val)
	{
		if (m_size == m_capacity)
		{
			reserve(m_capacity * 2);
		}

		m_pArr[m_size] = std::move(val);
		++m_size;
	}

	template< typename... Args >
	void emplace_back(Args&&... args)
	{
		if (m_size == m_capacity)
		{
			reserve(m_capacity * 2);
		}

		constructAtPlace(&m_pArr[m_size], std::forward<Args>(args)...);
		++m_size;
	}

	void pop_back()
	{
		if (m_size > 0)
		{
			m_pArr[m_size - 1].~dataType();
			--m_size;
		}
	}

	const dataType& front() const
	{
		return m_pArr[0];
	}
	
	dataType& front()
	{
		return m_pArr[0];
	}

	const dataType& back() const
	{
		return m_pArr[m_size - 1];
	}

	dataType& back()
	{
		return m_pArr[m_size - 1];
	}

	const dataType& at(size_t index) const
	{
		ASSERT(index <= m_size);
		return m_pArr[index];
	}

	dataType& at(size_t index)
	{
		ASSERT(index <= m_size);
		return m_pArr[index];
	}

	const dataType& operator[](size_t index) const
	{
		return m_pArr[index];
	}

	dataType& operator[](size_t index)
	{
		return m_pArr[index];
	}

	void erase(size_t index)
	{
		ASSERT(index <= m_size);
		m_pArr[index].~dataType();
		while (index < size())
		{
			m_pArr[index] = std::move(m_pArr[index + 1]);
			++index;
		}
		--m_size;
	}

private:

	template< typename... Args >
	void constructAtPlace(dataType *ptr, Args&&... args)
	{
		new (ptr) dataType(std::forward<Args>(args)...);
		//m_pArr[m_size] = dataType(std::forward<Args>(args)...);
	}

	void makeSpaceFor(dataType* ptr, size_t pos, size_t count)
	{
		for (size_t id = m_size + count - 1; id > (pos + count); --id)
		{
			ptr[id] = std::move(ptr[id - 1]);
		}
	}

private:
	dataType	*m_pArr{};
	size_t		m_capacity{};
	size_t		m_size{};
};
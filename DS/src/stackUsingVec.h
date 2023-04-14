#pragma once

#include <vector>

#include "Common/helper.h"

template <typename T>
class StackUsingVec
{
	using dataType = T;
public:
	StackUsingVec() = default;
	~StackUsingVec() { clear(); }

	size_t size() const { return m_top; }
	bool empty() const { return m_top == 0; }

	void clear()
	{
		m_vec.clear();
	}

	void push(dataType data)
	{
		m_vec.push_back(data);
	}

	void pop()
	{
		ASSERT(!empty());
		m_vec.pop_back();
	}
	
	const dataType& top() const
	{
		ASSERT(!empty());
		return m_vec.back();
	}

	dataType& top()
	{
		ASSERT(!empty());
		return m_vec.back();
	}

private:
	std::vector<dataType>		m_vec;
	size_t						m_top{};
};
#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <initializer_list>
#include <unordered_map>
#include <algorithm>
#include <vector>

#include "Common/testClass.h"
#include "Common/helper.h"

namespace nsCpp_DS {
// By Default min queue
template <typename TData = int, typename TPriority = int>
class PriorityQueue
{
public:
	using DataType				= TData;
	using PriorityType			= TPriority;

	using ComparatorType		= bool(*)(const DataType&, const DataType&);
	using GetPriorityFuncType	= typename PriorityType& (*) (DataType&);

public:
	constexpr static size_t npos = std::numeric_limits<size_t>::max();

	explicit PriorityQueue(ComparatorType cmpFunc = nullptr);

	PriorityQueue(std::initializer_list<DataType> ll, ComparatorType cmpFunc = nullptr);
	PriorityQueue(const std::vector<DataType>& vec, ComparatorType cmpFunc = nullptr);

	template <typename Iter>
	PriorityQueue(Iter first, Iter last, ComparatorType cmpFunc = nullptr);

	// Copy
	PriorityQueue(const PriorityQueue& other) = default;
	PriorityQueue& operator=(const PriorityQueue& other) = default;

	// Move
	PriorityQueue(PriorityQueue&& other) noexcept = default;
	PriorityQueue& operator=(PriorityQueue&& other) noexcept = default;

	bool empty() const { return m_arr.empty(); }
	size_t size() const { return m_arr.size(); };
	void clear() { m_arr.clear(); }

	// Register method to get priority
	void registerGetPriorityCallback(GetPriorityFuncType funcPtr) { m_getPriorityFunc = funcPtr; }

	// Insert
	void push(const DataType &value);
	void push(DataType &&value);

	// Accessors
	const DataType& front() const;
	DataType& front();

	// Modifiers
	void pop();
	void modify_priority(const DataType &value, const PriorityType newPriority);
	void erase(const DataType &value);

	// Display
	friend std::ostream& operator << (std::ostream& out, const PriorityQueue& pq) { pq.print(); return out; }
private:
	size_t getIndex(const DataType &value) const;

	template <typename T = DataType, typename std::enable_if<std::is_integral<T>{} || std::is_floating_point<T>{}, bool>::type = true>
	PriorityType& getPriority(const size_t index);

	PriorityType& getPriority(const size_t index);

	size_t getParentIndex(const size_t index) const;
	size_t getLeftChildIndex(const size_t index) const;
	size_t getRightChildIndex(const size_t index) const;

	void swimUp(const size_t index);
	void sinkDown(const size_t index);

	void print() const;

private:
	std::vector<DataType>		m_arr;
	ComparatorType				m_cmpFunc{};
	GetPriorityFuncType			m_getPriorityFunc{};
};

template <typename TData, typename TPriority>
PriorityQueue<TData, TPriority>::PriorityQueue(ComparatorType cmpFunc)
	: m_cmpFunc(cmpFunc)
{
	if (!m_cmpFunc)
	{
		m_cmpFunc = [](const DataType &a, const DataType &b) -> bool
		{
			return a > b;
		};
	}
}

template <typename TData, typename TPriority>
PriorityQueue<TData, TPriority>::PriorityQueue(std::initializer_list<DataType> ll, ComparatorType cmpFunc)
	: PriorityQueue(ll.begin(), ll.end(), cmpFunc)
{
}

template <typename TData, typename TPriority>
PriorityQueue<TData, TPriority>::PriorityQueue(const std::vector<DataType>& vec, ComparatorType cmpFunc)
	: PriorityQueue(vec.begin(), vec.end(), cmpFunc)
{
}

template <typename TData, typename TPriority>
template <typename Iter>
PriorityQueue<TData, TPriority>::PriorityQueue(Iter first, Iter last, ComparatorType cmpFunc)
	: PriorityQueue(cmpFunc)
{
	while (first != last)
	{
		push(*first++);
	}
}

// Insert
template <typename TData, typename TPriority>
void PriorityQueue<TData, TPriority>::push(const DataType &value)
{
	m_arr.push_back(value);
	swimUp(size() - 1);
}

template <typename TData, typename TPriority>
void PriorityQueue<TData, TPriority>::push(DataType &&value)
{
	m_arr.push_back(std::move(value));
	swimUp(size() - 1);
}

// Accessors
template <typename TData, typename TPriority>
const typename PriorityQueue<TData, TPriority>::DataType& PriorityQueue<TData, TPriority>::front() const
{
	assert(!m_arr.empty());
	return m_arr[0];
}

template <typename TData, typename TPriority>
typename PriorityQueue<TData, TPriority>::DataType& PriorityQueue<TData, TPriority>::front()
{
	assert(!m_arr.empty());
	return m_arr[0];
}

// Modifiers
template <typename TData, typename TPriority>
void PriorityQueue<TData, TPriority>::pop()
{
	assert(!m_arr.empty());
	const size_t pqSize = size();
	if (pqSize == 1)
	{
		m_arr.clear();
	}
	else
	{
		std::swap(m_arr[0], m_arr[pqSize - 1]);
		m_arr.pop_back();
		sinkDown(0);
	}
}

template <typename TData, typename TPriority>
void PriorityQueue<TData, TPriority>::modify_priority(const DataType &value, const PriorityType newPriority)
{
	assert(!m_arr.empty());
	size_t index = getIndex(value);
	if (index != npos)
	{
		getPriority(index) = newPriority;
		swimUp(index);
		sinkDown(index);
	}
}

template <typename TData, typename TPriority>
void PriorityQueue<TData, TPriority>::erase(const DataType &value)
{
	assert(!m_arr.empty());
	size_t index = getIndex(value);
	if (index != npos)
	{
		if (index == 0)
		{
			pop();
		}
		else
		{
			std::swap(m_arr[index], m_arr[m_arr.size() - 1]);
			m_arr.pop_back();
			swimUp(index);
		}
	}
}

// Private Methods
template <typename TData, typename TPriority>
size_t PriorityQueue<TData, TPriority>::getIndex(const DataType& value) const
{
	auto it = std::find(m_arr.begin(), m_arr.end(), value);
	return it == m_arr.end() ? npos : std::distance(m_arr.begin(), it);
}

template <typename TData, typename TPriority>
template <typename T, typename std::enable_if < std::is_integral<T>{} || std::is_floating_point<T>{}, bool > ::type >
typename PriorityQueue<TData, TPriority>::PriorityType& PriorityQueue<TData, TPriority>::getPriority(const size_t index)
{
	return m_arr[index];
}

template <typename TData, typename TPriority>
typename PriorityQueue<TData, TPriority>::PriorityType& PriorityQueue<TData, TPriority>::getPriority(const size_t index)
{
	return m_getPriorityFunc(m_arr[index]);
}

template <typename TData, typename TPriority>
size_t PriorityQueue<TData, TPriority>::getParentIndex(const size_t index) const
{
	return index > 0 ? (index - 1) / 2 : index;
}

template <typename TData, typename TPriority>
size_t PriorityQueue<TData, TPriority>::getLeftChildIndex(const size_t index) const
{
	return (index << 1) + 1;
}

template <typename TData, typename TPriority>
size_t PriorityQueue<TData, TPriority>::getRightChildIndex(const size_t index) const
{
	return (index << 1) + 2;
}

template <typename TData, typename TPriority>
void PriorityQueue<TData, TPriority>::swimUp(const size_t index)
{
	if (index > 0 && index < m_arr.size())
	{
		size_t parentId = getParentIndex(index);
		if (m_cmpFunc(m_arr[parentId], m_arr[index]) && index != parentId)
		{
			std::swap(m_arr[index], m_arr[parentId]);
			swimUp(parentId);
		}
	}
}

template <typename TData, typename TPriority>
void PriorityQueue<TData, TPriority>::sinkDown(const size_t index)
{
	if (index >= 0 && index < m_arr.size())
	{
		size_t ltChildId = getLeftChildIndex(index);
		size_t rtChildId = getRightChildIndex(index);

		size_t maxId = index;

		if (ltChildId < m_arr.size() && m_cmpFunc(m_arr[maxId], m_arr[ltChildId]))
		{
			maxId = ltChildId;
		}
		if (rtChildId < m_arr.size() && m_cmpFunc(m_arr[maxId], m_arr[rtChildId]))
		{
			maxId = rtChildId;
		}

		if (maxId != index)
		{
			std::swap(m_arr[index], m_arr[maxId]);
			sinkDown(maxId);
		}
	}
}

template <typename TData, typename TPriority>
void PriorityQueue<TData, TPriority>::print() const
{
	ns_Util::Logger::LOG_MSG("PriorityQueue [ ", size(), " ] :\n");
	ns_Util::printVector(m_arr);
	ns_Util::Logger::LOG_MSG("\n\n");
}

bool PriorityQueue_test_1()
{
	const char* testName = "Default Min Priority Queue of random int. Simple inserttion and retrival.";
	ns_Util::Logger::LOG_MSG("Executing Test 1 : ", testName, "\n\n");

	const size_t dataSize = 1000;

	int minVal = INT_MIN;
	int maxVal = INT_MAX;

	std::vector<int> inputValues = ns_Util::getVectorOfRandomInt(dataSize, minVal, maxVal);

	int testNum = 1;
	PriorityQueue pq(inputValues);

	std::vector<int> outputValues;
	while (!pq.empty())
	{
		outputValues.push_back(pq.front());
		pq.pop();
	}
	std::sort(inputValues.begin(), inputValues.end());

	if (inputValues.size() == outputValues.size() && inputValues == outputValues)
	{
		TEST_PASS;
	}
	else
	{
		TEST_FAIL;
		ns_Util::Logger::LOG_MSG("\nInput Vector size = ", inputValues.size(), ", Output Vector size = ", outputValues.size(), "\n\n");
		ASSERT;
		return false;
	}
	testNum++;

	ns_Util::Logger::LOG_MSG("\n\n");
	return true;
}

bool PriorityQueue_test_2()
{
	const char* testName = "Max Priority Queue of random int. Simple inserttion and retrival.";
	ns_Util::Logger::LOG_MSG("Executing Test 2 : ", testName, "\n\n");

	const size_t dataSize = 1000;

	int minVal = INT_MIN;
	int maxVal = INT_MAX;

	std::vector<int> inputValues = ns_Util::getVectorOfRandomInt(dataSize, minVal, maxVal);

	int testNum = 1;

	auto cmpFunc = +[](const typename PriorityQueue<int, int>::DataType& a, const typename PriorityQueue<int, int>::DataType& b) -> bool
	{
		return a < b;
	};

	PriorityQueue pq(inputValues, cmpFunc);

	std::vector<int> outputValues;
	while (!pq.empty())
	{
		outputValues.push_back(pq.front());
		pq.pop();
	}
	std::sort(inputValues.begin(), inputValues.end(), std::greater<>());

	if (inputValues.size() == outputValues.size() && inputValues == outputValues)
	{
		TEST_PASS;
	}
	else
	{
		TEST_FAIL;
		ns_Util::Logger::LOG_MSG("\nInput Vector size = ", inputValues.size(), ", Output Vector size = ", outputValues.size(), "\n\n");
		ASSERT;
		return false;
	}
	testNum++;

	ns_Util::Logger::LOG_MSG("\n\n");
	return true;
}

bool PriorityQueue_test_3()
{
	const char* testName = "Default Min Priority Queue of TestClass Object. Simple inserttion and retrival.";
	ns_Util::Logger::LOG_MSG("Executing Test 3 : ", testName, "\n\n");

	const size_t dataSize = 1000;

	int minVal = INT_MIN;
	int maxVal = INT_MAX;

	std::vector<int> inputValues = ns_Util::getVectorOfRandomInt(dataSize, minVal, maxVal);

	int testNum = 1;
	auto callBack = +[](ns_Util::TestClass<int>& testClass) -> typename ns_Util::TestClass<int>::value_type&
	{
		return testClass.getData();
	};

	PriorityQueue<ns_Util::TestClass<int>, int> pq;
	pq.registerGetPriorityCallback(callBack);
	for (auto x : inputValues)
	{
		pq.push(ns_Util::TestClass<int>(x, false));
	}

	std::vector<int> outputValues;
	while (!pq.empty())
	{
		outputValues.push_back(pq.front().getData());
		pq.pop();
	}

	std::sort(inputValues.begin(), inputValues.end());

	if (inputValues.size() == outputValues.size() && inputValues == outputValues)
	{
		TEST_PASS;
	}
	else
	{
		TEST_FAIL;
		ns_Util::Logger::LOG_MSG("\nInput Vector size = ", inputValues.size(), ", Output Vector size = ", outputValues.size(), "\n\n");
		ASSERT;
		return false;
	}
	testNum++;

	ns_Util::Logger::LOG_MSG("\n\n");
	return true;
}

bool PriorityQueue_testAll(const size_t runTestCount = 1)
{
	ns_Util::Logger::LOG_MSG("#####################################\n");
	LOG_ENTRY;
	const char* testName = "PriorityQueue_testAll :: ";
	for (size_t i = 1; i <= runTestCount; ++i)
	{
		ns_Util::Logger::LOG_MSG(testName, __LINE__, " : Test Counter : #", i, "\n\n");
		if (!PriorityQueue_test_1())
		{
			TEST_TYPE(" : PriorityQueue_test_1 : FAILED\n");
			return false;
		}
		if (!PriorityQueue_test_2())
		{
			TEST_TYPE(" : PriorityQueue_test_2 : FAILED\n");
			return false;
		}
		if (!PriorityQueue_test_3())
		{
			TEST_TYPE(" : PriorityQueue_test_3 : FAILED\n");
			return false;
		}
	}
	TEST_TYPE(" : ALL TEST :: PASS\n\n\n");
	LOG_EXIT;
	ns_Util::Logger::LOG_MSG("#####################################\n");
	return true;
}

}	// namespace nsCpp_DS

#endif	// #ifndef __PRIORITY_QUEUE_H__
#ifndef __HELPER_H__
#define __HELPER_H__

#include <iostream>
#include <algorithm>
#include <random>
#include <cassert>
#include "Common/logger.h"


#define ASSERT_ON_FAILURE


#define TEST_TYPE(str)				ns_Util::Logger::LOG_MSG("[ ", testName, " ] ", __LINE__, str);
#define TEST_PASS					ns_Util::Logger::LOG_MSG("[ ", testName, " ] ", __LINE__, " : Test # ", testNum, " PASS\n");
#define TEST_FAIL					ns_Util::Logger::LOG_MSG("[ ", testName, " ] ", __LINE__, " : Test # ", testNum, " FAIL\n");

#ifdef ASSERT_ON_FAILURE
	#define ASSERT assert(false)
#else	//#ifdef ASSERT_ON_FAILURE
	#define ASSERT
#endif	//#ifdef ASSERT_ON_FAILURE


#define PRINT_END_OF_DATA			if (f->addNewLineAtEnd()) {												\
										ns_Util::Logger::LOG_MSG(std::string(f->numOfLineAtEnd(), '\n'));	\
									}

#define GET_DELIMITER				std::string del = ", ";				\
									if (f->printDataPerLine()) {		\
										del = std::string(1, '\n');		\
									}

#define LOG_ENTRY_CLASS				ns_Util::Logger::LOG_MSG(m_className, __func__, "() -->Entry\n")
#define LOG_EXIT_CLASS				ns_Util::Logger::LOG_MSG(m_className, __func__, "() -->Exit\n\n")

#define LOG_ENTRY					ns_Util::Logger::LOG_MSG("Free Function : ", __func__, "() -->Entry\n")
#define LOG_EXIT					ns_Util::Logger::LOG_MSG("Free Function : ", __func__, "() -->Exit\n\n")


namespace ns_Util
{
using size_type = size_t;

struct Formatter
{
	static Formatter* getFormatter()
	{
		static Formatter f;
		return &f;
	}

	static void numOfLineAtEnd(int num) { m_nNumOfNewLines = num; }
	static void printSize(bool b) { m_bPrintSize = b; }
	static void printCapacity(bool b) { m_bPrintCapacity = b; }
	static void printDataPerLine(bool b) { m_bPrintDataPerLine = b; }
	static void addNewLineAtEnd(bool b) { m_bAddNewLineAtEnd = b; }


	static int numOfLineAtEnd() { return m_nNumOfNewLines; }
	static bool printSize() { return m_bPrintSize; }
	static bool printCapacity() { return m_bPrintCapacity; }
	static bool printDataPerLine() { return m_bPrintDataPerLine; }
	static bool addNewLineAtEnd() { return m_bAddNewLineAtEnd; }
private:
	Formatter() = default;

private:
	static int		m_nNumOfNewLines;
	static bool		m_bPrintCapacity;
	static bool		m_bPrintSize;
	static bool		m_bPrintDataPerLine;
	static bool		m_bAddNewLineAtEnd;
};

int Formatter::m_nNumOfNewLines{ 1 };
bool Formatter::m_bPrintCapacity{ false };
bool Formatter::m_bPrintSize{ false };
bool Formatter::m_bPrintDataPerLine{ false };
bool Formatter::m_bAddNewLineAtEnd{ true };

// Inclusive range [min, max]
static inline int getRandomNumber(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_int_distribution<> distrib(min, max);

	return distrib(gen);
}

// Inclusive range [min, max]
std::vector<int> getVectorOfRandomInt(const size_t size, const int min, const int max)
{
	std::vector<int> inputValues(size);			// vec of val
	for (size_t i = 0; i < size; ++i)
	{
		inputValues[i] = ns_Util::getRandomNumber(min, max);
	}
	return inputValues;
}

template <typename T>
std::pair<std::pair<size_t, size_t>, bool> findMismatch(const std::vector<T>& expected, const std::vector<T>& output)
{
	std::pair<std::pair<size_t, size_t>, bool> rt;

	std::pair<std::vector<T>::const_iterator, std::vector<T>::const_iterator> retPair;

	retPair = std::mismatch(expected.cbegin(), expected.cend(), output.cbegin());

	if (retPair.first == expected.cend() && retPair.second == output.cend())
	{
		rt.second = false;
	}
	else
	{
		rt.second = true;
		rt.first.first = std::distance(expected.cbegin(), retPair.first);
		rt.first.second = std::distance(output.cbegin(), retPair.second);
	}
	return rt;
}

template <typename T, typename Predicate>
std::pair<std::pair<size_t, size_t>, bool> findMismatch(const std::vector<T>& expected, const std::vector<T>& output, Predicate predicate)
{
	std::pair<std::pair<size_t, size_t>, bool> rt;

	std::pair<std::vector<T>::const_iterator, std::vector<T>::const_iterator> retPair;

	retPair = std::mismatch(expected.cbegin(), expected.cend(), output.cbegin(), predicate);

	if (retPair.first == expected.cend() && retPair.second == output.cend())
	{
		rt.second = false;
	}
	else
	{
		rt.second = true;
		rt.first.first = std::distance(expected.cbegin(), retPair.first);
		rt.first.second = std::distance(output.cbegin(), retPair.second);
	}
	return rt;
}

// Data Printing
template<typename T>
void printArray(const T* arr, const size_type size, const char* msg = nullptr)
{
	if (msg)
	{
		Logger::LOG_MSG(msg);
	}
	const Formatter* f = Formatter::getFormatter();

	if (f->printSize())
	{
		Logger::LOG_MSG("Array [size = ", size, " ] : ");
	}

	GET_DELIMITER;

	for (size_type i = 0; i < size; ++i)
	{
		Logger::LOG_MSG(arr[i], del);
	}

	PRINT_END_OF_DATA;
}

template<typename T>
void printArray(const T* arr, const size_type low, const size_type high, const char* msg = nullptr)
{
	if (msg)
	{
		Logger::LOG_MSG(msg);
	}
	const Formatter* f = Formatter::getFormatter();

	if (f->m_bPrintSize())
	{
		Logger::LOG_MSG("Array [low = ", low, ", high = ", high, " ] : ");
	}

	GET_DELIMITER;

	for (size_type i = low; i < high; ++i)
	{
		Logger::LOG_MSG(arr[i], del);
	}

	PRINT_END_OF_DATA;
}

template<typename V>
void printVector(const V& vec, const char* msg = nullptr)
{
	if (msg)
	{
		Logger::LOG_MSG(msg);
	}
	const Formatter* f = Formatter::getFormatter();

	if (f->printSize())
	{
		Logger::LOG_MSG("Vector ");
		Logger::LOG_MSG("[size = ", vec.size(), " ], ");
	}

	if (f->printCapacity())
	{
		if (!(f->printSize()))
		{
			Logger::LOG_MSG("Vector ");
		}
		Logger::LOG_MSG("[capacity = ", vec.capacity(), " ], ");
	}

	GET_DELIMITER;

	for (size_type i = 0, size = vec.size(); i < size; ++i)
	{
		Logger::LOG_MSG(vec[i], del);
	}

	PRINT_END_OF_DATA;
}

template<typename Iter>
void printVector(Iter beg, Iter end, const char* msg = nullptr)
{
	if (msg)
	{
		Logger::LOG_MSG(msg);
	}
	const Formatter* f = Formatter::getFormatter();

	if (f->printSize())
	{
		Logger::LOG_MSG("Vector ");
		Logger::LOG_MSG("[Element = ", std::distance(beg, end), " ], ");
	}

	GET_DELIMITER;

	while (beg != end)
	{
		Logger::LOG_MSG(*beg, del);
		++beg;
	}

	PRINT_END_OF_DATA;
}

template<typename NodeType>
void printList(const NodeType * nodePtr, size_type size, const char* msg = nullptr)
{
	if (msg)
	{
		Logger::LOG_MSG(msg);
	}

	const Formatter* f = Formatter::getFormatter();
	if (!nodePtr)
	{
		ns_Util::Logger::LOG_MSG("Empty LinkList\n");
		return;
	}

	if (f->printSize())
	{
		ns_Util::Logger::LOG_MSG("LinkList [ ", size, " ] : \n");
	}

	GET_DELIMITER;
	size_t i = 1;
	while (nodePtr)
	{
		ns_Util::Logger::LOG_MSG("Node #", i++, ": ", *nodePtr, '\n');
		nodePtr = nodePtr->m_next;
	}

	PRINT_END_OF_DATA;
}
}

#endif //#ifndef __HELPER_H__
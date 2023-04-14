#ifndef __TEST_CLASS_H__
#define __TEST_CLASS_H__

#include <string>
#include "Common/logger.h"

namespace ns_Util
{
template <typename T = int>
class TestClass;

template<typename T> // declaration
std::ostream& operator<< (std::ostream&, const TestClass<T>&);

template <typename T>
class TestClass
{
public:
	using value_type	= T;
	using pointer_type	= T*;
public:
	~TestClass();
	explicit TestClass(bool printStats = true);
	explicit TestClass(const value_type& val, bool printStats = true);
	TestClass(const value_type& val, const pointer_type ptr, bool printStats = true);
	TestClass(const TestClass& other);
	TestClass(TestClass&& other) noexcept;

	TestClass& operator = (const TestClass& other);
	TestClass& operator = (TestClass&& other) noexcept;

	const value_type& getData() const;
	value_type& getData();

	void setData(const value_type& val);

	const pointer_type getPtr() const;
	pointer_type getPtr();

	void setPtr(pointer_type ptr);

	static void resetCounter() { m_sCounter = 0; };
	static size_t getCounter() { return m_sCounter; };

	bool operator<(const TestClass& other) const;
	bool operator>(const TestClass& other) const;
	bool operator==(const TestClass& other) const;
	bool operator!=(const TestClass& other) const;

	friend std::ostream& operator<< <T>(std::ostream& out, const TestClass<T>& t);

private:
	value_type			m_data{};
	pointer_type		m_pPtr{};
	std::string			m_className{"TestClass : "};
	bool				m_bPrintStats{ true };
	static size_t		m_sCounter;
};

template <typename T>
size_t TestClass<T>::m_sCounter = 0;

template <typename T>
TestClass<T>::~TestClass()
{
	delete m_pPtr;
	m_pPtr = nullptr;
	m_bPrintStats ? Logger::LOG_MSG(m_className, " Dtor\n") : void();
}

template <typename T>
TestClass<T>::TestClass(bool printStats)
	: m_bPrintStats(printStats)
{
	m_sCounter++;
	m_pPtr = new value_type(m_data + 1);
	m_bPrintStats ? Logger::LOG_MSG(m_className, " Default Ctor\n") : void();
}

template <typename T>
TestClass<T>::TestClass(const value_type& val, bool printStats)
	: m_data(val)
	, m_bPrintStats(printStats)
{
	m_sCounter++;
	m_pPtr = new value_type(m_data + 1);
	m_bPrintStats ? Logger::LOG_MSG(m_className, " Parameterized Ctor 1 : val = ", m_data, '\n') : void();
}


template <typename T>
TestClass<T>::TestClass(const value_type& val, const pointer_type ptr, bool printStats)
	: m_data(val)
	, m_bPrintStats(printStats)
{
	m_sCounter++;
	m_bPrintStats ? Logger::LOG_MSG(m_className, " Parameterized Ctor 2 : val = ", m_data) : void();
	if (ptr)
	{
		m_pPtr = new value_type(*ptr);
		m_bPrintStats ? Logger::LOG_MSG(", ptr = ", ptr, ", *ptr", *ptr, '\n') : void();
	}
	else
	{
		m_bPrintStats ? Logger::LOG_MSG(", ptr = nullptr\n") : void();
	}
}

template <typename T>
TestClass<T>::TestClass(const TestClass &other)
	: m_data(other.m_data)
	, m_bPrintStats(other.m_bPrintStats)
{
	m_sCounter++;
	m_bPrintStats ? Logger::LOG_MSG(m_className, " Copy Ctor : val = ", m_data) : void();
	if (other.m_pPtr)
	{
		m_pPtr = new value_type(*(other.m_pPtr));
		m_bPrintStats ? Logger::LOG_MSG(", ptr = ", other.m_pPtr, ", *ptr", *(other.m_pPtr), '\n') : void();
	}
	else
	{
		m_bPrintStats ? Logger::LOG_MSG(", ptr = nullptr\n") : void();
	}
}

template <typename T>
TestClass<T>::TestClass(TestClass&& other) noexcept
{
	m_sCounter++;
	m_data = std::exchange(other.m_data, value_type{});
	m_pPtr = std::exchange(other.m_pPtr, nullptr);
	m_bPrintStats = other.m_bPrintStats;

	m_bPrintStats ? Logger::LOG_MSG(m_className, " Move Ctor : val = ", m_data) : void();
	if (m_pPtr)
	{
		m_bPrintStats ? Logger::LOG_MSG(", ptr = ", m_pPtr, ", *ptr", *m_pPtr, '\n') : void();
	}
	else
	{
		m_bPrintStats ? Logger::LOG_MSG(", ptr = nullptr\n") : void();
	}
}

template <typename T>
TestClass<T>& TestClass<T>::operator=(const TestClass& other)
{
	if (this != &other)
	{
		m_data = other.m_data;
		m_bPrintStats = other.m_bPrintStats;

		m_bPrintStats ? Logger::LOG_MSG(m_className, " Copy assignment operator : val = ", m_data) : void();
		if (other.m_pPtr)
		{
			*m_pPtr = *(other.m_pPtr);
			m_bPrintStats ? Logger::LOG_MSG(", ptr = ", m_pPtr, ", *ptr", *m_pPtr, '\n') : void();
		}
		else
		{
			delete m_pPtr;
			m_pPtr = nullptr;
			m_bPrintStats ? Logger::LOG_MSG(", ptr = nullptr\n") : void();
		}
	}
	return *this;
}

template <typename T>
TestClass<T>& TestClass<T>::operator=(TestClass&& other) noexcept
{
	if (this != &other)
	{
		delete m_pPtr;
		m_data = std::exchange(other.m_data, value_type{});
		m_pPtr = std::exchange(other.m_pPtr, nullptr);
		m_bPrintStats = other.m_bPrintStats;

		m_bPrintStats ? Logger::LOG_MSG(m_className, " Move assignment operator : val = ", m_data) : void();
		if (m_pPtr)
		{
			m_bPrintStats ? Logger::LOG_MSG(", ptr = ", m_pPtr, ", *ptr", *m_pPtr, '\n') : void();
		}
		else
		{
			m_bPrintStats ? Logger::LOG_MSG(", ptr = nullptr\n") : void();
		}
	}
	return *this;
}

template <typename T>
const typename TestClass<T>::value_type& TestClass<T>::getData() const
{
	m_bPrintStats ? Logger::LOG_MSG(m_className, "const T& getData() const\n") : void();
	return m_data;
}

template <typename T>
typename TestClass<T>::value_type& TestClass<T>::getData()
{
	m_bPrintStats ? Logger::LOG_MSG(m_className, "T& getData()\n") : void();
	return m_data;
}

template <typename T>
void TestClass<T>::setData(const value_type& val)
{
	m_bPrintStats ? Logger::LOG_MSG(m_className, "void setData(const T &val)\n") : void();
	m_data = val;
}

template <typename T>
const typename TestClass<T>::pointer_type TestClass<T>::getPtr() const
{
	m_bPrintStats ? Logger::LOG_MSG(m_className, "const T* getPtr() const\n") : void();
	return m_pPtr;
}

template <typename T>
typename TestClass<T>::pointer_type TestClass<T>::getPtr()
{
	m_bPrintStats ? Logger::LOG_MSG(m_className, "T* getPtr()\n") : void();
	return m_pPtr;
}

template <typename T>
void TestClass<T>::setPtr(pointer_type ptr)
{
	m_bPrintStats ? Logger::LOG_MSG(m_className, "void setPtr(T *ptr)\n") : void();
	delete m_pPtr;
	m_pPtr = std::exchange(ptr, nullptr);
}

template <typename T>
bool TestClass<T>::operator<(const TestClass<T>& other) const
{
	return (m_data < other.m_data) && ((m_pPtr && other.m_pPtr) ? (*m_pPtr < *(other.m_pPtr)) : true);
}

template <typename T>
bool TestClass<T>::operator>(const TestClass<T>& other) const
{
	return other.operator<(*this);
}

template <typename T>
bool TestClass<T>::operator==(const TestClass<T>& other) const
{
	return !(this->operator<(other)) && !(other.operator<(*this));
}

template <typename T>
bool TestClass<T>::operator!=(const TestClass<T>& other) const
{
	return !(this->operator==(other));
}

template <typename T>
std::ostream& operator<< <T>(std::ostream& out, const TestClass<T>& t)
{
	t.m_bPrintStats ? Logger::LOG_MSG(t.m_className, " val = ", t.m_data) : void();
	if (t.m_pPtr)
	{
		t.m_bPrintStats ? Logger::LOG_MSG(", ptr = ", t.m_pPtr, ", *ptr", *(t.m_pPtr), '\n') : void();
	}
	else
	{
		t.m_bPrintStats ? Logger::LOG_MSG(", ptr = nullptr\n") : void();
	}
	return out;
}
}

#endif //#ifndef __TEST_CLASS_H__
#ifndef __CPP_FEATURES_H__
#define __CPP_FEATURES_H__

#include "Common/logger.h"
#include "Common/helper.h"
#include <string>
#include <functional>

namespace ns_Util
{
class CppFeatures
{
public:
	static void lambdaTypeIdExample();
	static void placementNewExample_1();
	static void placementNewExample_2();
	static void allocatorExample_1();
	static void allocatorExample_2();
	static void allocatorExample_3();
private:
	static const std::string		m_className;
};

const std::string CppFeatures::m_className{ "CppFeatures : " };

void CppFeatures::lambdaTypeIdExample()
{
	LOG_ENTRY_CLASS;
	auto func1 = []() -> void {
		Logger::LOG_MSG("Function 1 : Lambda.\n");
	};

	auto func2 = +[]() -> void {
		Logger::LOG_MSG("Function 2 : Lambda converted to c-style function pointer.\n");
	};

	std::function<void()> ff;

	Logger::LOG_MSG("ff = std::function<void()>       , typeid(ff).name()", typeid(ff).name(), '\n');
	Logger::LOG_MSG("func1 = Lambda                   , typeid(func1).name()", typeid(func1).name(), '\n');
	Logger::LOG_MSG("func2 = Lambda prefixed with '+' , typeid(func2).name()", typeid(func2).name(), '\n');
	Logger::LOG_MSG("C-style function pointer         , typeid(void(*)()).name()", typeid(void(*)()).name(), '\n');
	LOG_EXIT_CLASS;
}

void CppFeatures::placementNewExample_1()
{
	LOG_ENTRY_CLASS;
	int integer = 10;
	double fp{ 20.5555555555555 };

	size_t size = sizeof(integer);
	size += sizeof(fp);

	// new operator
	char* ptr = new char[size];

	// placement new operator
	int* intPtr = new (ptr) int(integer);
	double* fpPtr = new (ptr + sizeof(integer)) double(fp);

	Logger::LOG_MSG("integer = ", integer, '\n');
	Logger::LOG_MSG("double  = ", fp, '\n');

	Logger::LOG_MSG("*intPtr = ", *intPtr, '\n');
	Logger::LOG_MSG("*fpPtr  = ", *fpPtr, '\n');

	delete[] ptr;
	LOG_EXIT_CLASS;
}

void CppFeatures::placementNewExample_2()
{
	LOG_ENTRY_CLASS;
	using classType = ns_Util::TestClass<double>;
	size_t objSize_A = sizeof(size_t);

	Logger::LOG_MSG("sizeof(size_t)                      = ", objSize_A, '\n');
	size_t objSize_B = sizeof(classType);
	Logger::LOG_MSG("sizeof(ns_Util::TestClass<double>)  = ", objSize_B, '\n');

	char* ptr = new char[objSize_A + objSize_B];

	size_t* ptrSize = new (ptr) size_t(10);
	classType* ptrTestClass = new (ptr + objSize_A) classType();

	Logger::LOG_MSG("ptrSize        = ", ptrSize, '\n');
	Logger::LOG_MSG("ptrTestClass   = ", ptrTestClass, '\n');

	Logger::LOG_MSG("*ptrSize       = ", *ptrSize, '\n');
	Logger::LOG_MSG("*ptrTestClass  = ", *ptrTestClass, '\n');

	ptrTestClass->~TestClass();	// important

	delete[] ptr;
	LOG_EXIT_CLASS;
}

void CppFeatures::allocatorExample_1()
{
	LOG_ENTRY_CLASS;

	// int allocator
	std::allocator<int> intAllocator;
	using intAllocator_t = std::allocator_traits<decltype(intAllocator)>;

	size_t size = 10;
	int *arr = intAllocator_t::allocate(intAllocator, size);
	memset(arr, 0, sizeof(int) * size);
	arr[3] = 9999;
	arr[9] = 7;

	printArray(arr, size);
	intAllocator_t::destroy(intAllocator, arr);
	intAllocator_t::deallocate(intAllocator, arr, size);
	arr = nullptr;

	// std::string allocator
	using stringAllocatorType = std::allocator<std::string>;
	using stringAllocator_t = std::allocator_traits<stringAllocatorType>;
	stringAllocator_t::rebind_alloc<std::string> stringAllocator = stringAllocatorType();
	
	size = 2;
	std::string *strArr = stringAllocator_t::allocate(stringAllocator, size);
	stringAllocator_t::construct(stringAllocator, &strArr[0], "Hello");
	stringAllocator_t::construct(stringAllocator, &strArr[1], "Bar");

	printArray(strArr, size);
	for (size_t i = 0; i < size; ++i)
	{
		stringAllocator_t::destroy(stringAllocator, &strArr[i]);
	}
	stringAllocator_t::deallocate(stringAllocator, strArr, size);
	strArr = nullptr;

	LOG_EXIT_CLASS;
}

void CppFeatures::allocatorExample_2()
{
	LOG_ENTRY_CLASS;

	EasyAllocator<std::wstring> ws;
	size_t size = 3;

	std::wstring* wsPtr = ws.allocate(size);

	ws.construct(&wsPtr[0], L"Hello");
	ws.construct(&wsPtr[1], L"Wow");
	ws.construct(&wsPtr[2], L"Last");
	
	printArray(wsPtr, size);
	
	for (size_t i = size; i--;)
	{
		ws.destroy(&wsPtr[i]);
	}
	ws.deallocate(wsPtr, size);
	wsPtr = nullptr;

	LOG_EXIT_CLASS;
}

void CppFeatures::allocatorExample_3()
{
	LOG_ENTRY_CLASS;

	EasyAllocator<TestClass<int>> alloc;
	size_t size = 3;

	TestClass<int>* testPtr = alloc.allocate(size);

	alloc.construct(&testPtr[0], 10, new int(11));
	alloc.construct(&testPtr[1], 12, new int(13));
	alloc.construct(&testPtr[2], 14, new int(15));

	printArray(testPtr, size);

	for (size_t i = size; i--;)
	{
		alloc.destroy(&testPtr[i]);
	}
	alloc.deallocate(testPtr, size);
	testPtr = nullptr;

	LOG_EXIT_CLASS;
}
void test_CppFeatures()
{
	LOG_ENTRY;
	CppFeatures::lambdaTypeIdExample();
	CppFeatures::placementNewExample_1();
	CppFeatures::placementNewExample_2();
	CppFeatures::allocatorExample_1();
	CppFeatures::allocatorExample_2();
	CppFeatures::allocatorExample_3();
	LOG_EXIT;
}


}	// namespace ns_Util

#endif //#ifndef __CPP_FEATURES_H__
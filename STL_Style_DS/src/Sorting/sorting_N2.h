#ifndef __SORTING_N_2_H__
#define __SORTING_N_2_H__

#include <vector>

#include "Common/logger.h"
#include "Common/helper.h"

namespace nsCpp_DS {
class SortingN2
{
	using size_type = size_t;
public:
	template<typename T>
	static void insertionSort(T* arr, const size_type size)
	{
		if (!arr)
		{
			return;
		}
		T key{};
		for (size_type i = 1, j = 0; i < size; ++i)
		{
			key = arr[i];
			j = i;

			while (j-- && arr[j] > key)
			{
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = key;
		}
	}

	template<typename T>
	static void insertionSort(std::vector<T> &vec)
	{
		insertionSort(vec.data(), vec.size());
	}

	template<typename T>
	static void selectionSort(T* arr, const size_type size)
	{
		if (!arr)
		{
			return;
		}
		for (size_type i = 0, minIndex = 0; i < size; ++i)
		{
			minIndex = i;
			for (size_type j = i + 1; j < size; ++j)
			{
				if (arr[minIndex] > arr[j])
				{
					minIndex = j;
				}
			}
			std::swap(arr[i], arr[minIndex]);
		}
	}

	template<typename T>
	static void selectionSort(std::vector<T>& vec)
	{
		selectionSort(vec.data(), vec.size());
	}

	template<typename T>
	static void bubbleSort(T* arr, const size_type size)
	{
		if (!arr)
		{
			return;
		}
		bool bStop = false;
		for (size_type i = 0; i < size - 1 && !bStop; ++i)
		{
			bStop = true;
			for (size_type j = 0; j < size - i - 1; ++j)
			{
				if (arr[j] > arr[j + 1])
				{
					std::swap(arr[j], arr[j + 1]);
					bStop = false;
				}
			}
		}
	}

	template<typename T>
	static void bubbleSort(std::vector<T>& vec)
	{
		bubbleSort(vec.data(), vec.size());
	}

	template<typename T>
	static void bubbleSortRecursive(T *arr, const size_type size)
	{
		if (!arr || size == 1)
		{
			return;
		}

		for (size_type i = 0; i < size - 1; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				std::swap(arr[i], arr[i + 1]);
			}
		}
		bubbleSortRecursive(arr, size - 1);
	}

	template<typename T>
	static void bubbleSortRecursive(std::vector<T>& vec)
	{
		bubbleSortRecursive(vec.data(), vec.size());
	}
};

void test_SortingN2_1()
{
	const char* testName = "Insertion | Selection | Bubble | BubbleRecursive Sort test with C-Style array.";
	ns_Util::Logger::LOG_MSG("Executing Test 1 : ", testName, "\n\n");

	int arr[] = { 64, 25, 12, 22, 11 };
	size_t size = sizeof(arr) / sizeof(arr[0]);

	SortingN2::insertionSort(arr, size);

	int arr1[] = { 64, 34, 25, 12, 22, 90, 11 };
	size = sizeof(arr1) / sizeof(arr1[0]);

	SortingN2::selectionSort(arr, size);

	int arr2[] = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	size = sizeof(arr2) / sizeof(arr2[0]);

	SortingN2::bubbleSort(arr2, size);
}

void test_SortingN2_2()
{
	const char* testName = "Insertion | Selection | Bubble | BubbleRecursive Sort test with std::vector.";
	ns_Util::Logger::LOG_MSG("Executing Test 2 : ", testName, "\n\n");

	std::vector<int> vec = { 64, 25, 12, 22, 11 };
	SortingN2::insertionSort(vec);

	vec = { 64, 34, 25, 12, 22, 90, 11 };
	SortingN2::selectionSort(vec);

	vec = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	SortingN2::bubbleSort(vec);
}

void test_SortingN2()
{
	LOG_ENTRY;
	test_SortingN2_1();
	test_SortingN2_2();
	LOG_EXIT;
	ns_Util::Logger::LOG_MSG("#####################################\n");
}

}	// namespace nsCpp_DS

#endif // #ifndef __SORTING_N_2_H__
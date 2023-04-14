#ifndef __SORTING_N_LOG_N_H__
#define __SORTING_N_LOG_N_H__

#include <vector>
#include <thread>
#include <chrono>

#include "Common/logger.h"
#include "Common/helper.h"


namespace nsCpp_DS {
class SortingNLogN
{
	using size_type = size_t;
public:
	// 1. QuickSort
	template<typename T, typename Comparator = std::less<T>>
	static void quickSort(T* arr, const size_type size)
	{
		Comparator cmpFunc;
		quickSort_Helper(arr, 0, size - 1, cmpFunc);
	}

	template<typename T, typename Comparator = std::less<T>>
	static void quickSort(std::vector<T> vec)
	{
		quickSort<T, Comparator>(vec.data(), vec.size());
	}

	// 2. MergeSort
	// 2.1 MergeSort_1
	template<typename T, typename Comparator = std::less_equal<T>>
	static void mergeSort_1(T* arr, const size_type size)
	{
		mergeSort_1_Helper(arr, 0, size - 1, Comparator());
	}

	template<typename T, typename Comparator = std::less_equal<T>>
	static void mergeSort_1(std::vector<T> &vec)
	{
		mergeSort_1<T, Comparator>(vec.data(), vec.size());
	}

	// 2.2 MergeSort_2
	template<typename T, typename Comparator = std::less_equal<T>>
	static void mergeSort_2(T* arr, const size_type size)
	{
		T* arrCopy = new T[size];
		
		copyData(arr, 0, size, arrCopy);

		mergeSort_2_Helper(arrCopy, 0, size, arr, Comparator());

		delete[] arrCopy;
	}

	template<typename T, typename Comparator = std::less_equal<T>>
	static void mergeSort_2(std::vector<T> &vec)
	{
		mergeSort_2<T, Comparator>(vec.data(), vec.size());
	}

	// 3. HeapSort
	template<typename T, typename Comparator = std::greater<T>>
	static void heapSort(T* arr, const size_type size)
	{
		Comparator cmpFunc;
		for (size_t i = getParentIndex(size) + 1; i--;)
		{
			heapify(arr, size, i, cmpFunc);
		}

		for (size_t i = size - 1; i > 0; --i)
		{
			std::swap(arr[0], arr[i]);
			heapify(arr, i, 0, cmpFunc);
		}
	}

	template<typename T, typename Comparator = std::greater<T>>
	static void heapSort(std::vector<T> &vec)
	{
		heapSort<T, Comparator>(vec.data(), vec.size());
	}
private:
	// Common Helper's
	static int64_t getParentIndex(const int64_t index)	// 0-Based indexing
	{
		return (index - 1) / 2;
	}

	static int64_t getLeftChildIndex(const int64_t index)	// 0-Based indexing
	{
		return (index << 1) + 1;
	}

	static int64_t getRightChildIndex(const int64_t index)	// 0-Based indexing
	{
		return (index << 1) + 2;
	}

	static int64_t getMid(const int64_t low, const int64_t high)
	{
		return low + (high - low) / 2;
	}

	template<typename T>
	static void copyData(T* srcArr, size_type low, const size_type high, T* destArr)
	{
		while (low < high)
		{
			destArr[low] = srcArr[low];
			low++;
		}
	}

	// 1. QuickSort
	template<typename T, typename Comparator>
	static void quickSort_Helper(T* arr, int64_t low, int64_t high, const Comparator &cmpFunc)
	{
		if (low < high)
		{
			int64_t partitionIndex = partition(arr, low, high, cmpFunc);
			quickSort_Helper(arr, low, partitionIndex, cmpFunc);
			quickSort_Helper(arr, partitionIndex + 1, high, cmpFunc);
		}
	}

	template<typename T, typename Comparator>
	static int64_t partition(T* arr, int64_t low, int64_t high, const Comparator &cmpFunc)
	{
		//const T& pivotValue = arr[getMid(low, high)];
		const T& pivotValue = arr[low];
		
		low--;
		high++;

		while (true)
		{
			while (cmpFunc(arr[++low], pivotValue));

			while (cmpFunc(pivotValue, arr[--high]));
			
			if (low >= high)
			{
				break;
			}
			std::swap(arr[low--], arr[high++]);
		}
		return high;
	}

	// 2. MergeSort
	// 2.1 MergeSort_1
	template<typename T, typename Comparator>
	static void mergeSort_1_Helper(T* arr, size_type lt, size_type rt, const Comparator& cmpFunc)
	{
		if (lt >= rt)
		{
			return;
		}
		const size_type mid = getMid(lt, rt);

		mergeSort_1_Helper(arr, lt, mid, cmpFunc);
		mergeSort_1_Helper(arr, mid + 1, rt, cmpFunc);

		merge_1(arr, lt, mid, rt, cmpFunc);
	}

	template<typename T, typename Comparator>
	static void merge_1(T* arr, size_type lt, size_type mid, size_type rt, const Comparator& cmpFunc)
	{
		const size_type n1 = mid - lt + 1;
		const size_type n2 = rt - mid;

		T* left = new T[n1];
		T* right = new T[n2];

		/* Copy data to temp arrays */
		size_type i{}, j{};
		for (i = 0; i < n1; ++i)
		{
			left[i] = std::move(arr[lt + i]);
		}

		for (j = 0; j < n2; ++j)
		{
			right[j] = std::move(arr[mid + 1 + j]);
		}

		i = j = 0;
		while (i < n1 && j < n2)
		{
			if (cmpFunc(left[i], right[j]))
			{
				arr[lt++] = std::move(left[i++]);
			}
			else
			{
				arr[lt++] = std::move(right[j++]);
			}
		}

		while (i < n1)
		{
			arr[lt++] = std::move(left[i++]);
		}

		while (j < n2)
		{
			arr[lt++] = std::move(right[j++]);
		}
		delete[] left;
		delete[] right;
	}

	// 2.1 MergeSort_2
	template<typename T, typename Comparator>
	static void mergeSort_2_Helper(T* arrCopy, size_type low, size_type high, T* arr, const Comparator& cmpFunc)
	{
		if (high - low <= 1)
			return;

		const size_type mid = getMid(low, high);

		mergeSort_2_Helper(arr, low, mid, arrCopy, cmpFunc);
		mergeSort_2_Helper(arr, mid, high, arrCopy, cmpFunc);

		merge_2(arrCopy, low, mid, high, arr, cmpFunc);
	}

	template<typename T, typename Comparator>
	static void merge_2(T* arr, size_type low, const size_type mid, const size_type high, T* arrCopy, const Comparator& cmpFunc)
	{
		size_type s1 = low;
		size_type s2 = mid;

		for (size_type k = low; k < high; ++k)
		{
			if (s1 < mid && (s2 >= high || cmpFunc(arr[s1], arr[s2])))
			{
				arrCopy[k] = arr[s1++];
			}
			else
			{
				arrCopy[k] = arr[s2++];
			}
		}
	}

	// 3. HeapSort
	template<typename T, typename Comparator>
	static void heapify(T* arr, size_type size, size_type i, const Comparator& cmpFunc)
	{
		size_type largest = i;
		size_type leftID = getLeftChildIndex(i);
		size_type rightID = getRightChildIndex(i);

		if (leftID < size && cmpFunc(arr[leftID], arr[largest]))
		{
			largest = leftID;
		}
		if (rightID < size && cmpFunc(arr[rightID], arr[largest]))
		{
			largest = rightID;
		}
		if (largest != i)
		{
			std::swap(arr[i], arr[largest]);
			heapify(arr, size, largest, cmpFunc);
		}
	}
};

void matchArrays(const std::vector<int>& vecA, const std::vector<int>& vecB)
{
	int packetSize = 10;
	for (size_t i = 0, size = vecA.size(); i < size; i += packetSize)
	{
		for (int j = 0; j < packetSize; ++j)
		{
			ns_Util::Logger::LOG_MSG("[ ", i + j, " ] vecA = ", vecA[i + j], ", vecB = ", vecB[i + j]);
			if (vecA[i + j] != vecB[i + j])
			{
				ns_Util::Logger::LOG_MSG("          Mismatch : vecA[ ", i + j, " ] = ", vecA[i + j], ", vecB[ ", i + j, " ] = ", vecB[i + j], '\n');
				//ASSERT;
			}
			ns_Util::Logger::LOG_MSG("\n\n");
		}
		ns_Util::Logger::LOG_MSG("\n\nFrom Index [ ", i, " , ", i + 10, " ] matched.\n");
	}
}

void test_SortingNLogN_1()
{
	const char* testName = "N_LOG_N Sort";
	const size_t size = 1000;
	
	ns_Util::Logger::LOG_MSG("Executing Test 1 : ", testName, "\n");
	int minVal = INT_MIN;
	int maxVal = INT_MAX;
	ns_Util::Logger::LOG_MSG("Data Size : ", size, ", of random int between [ ", minVal, ", ", maxVal, " ]\n\n");

	const std::vector<int> dataVec = ns_Util::getVectorOfRandomInt(size, minVal, maxVal);
	auto stl_sorted_arr = dataVec;
	auto arr = dataVec;
	int testNum = 1;

	std::sort(stl_sorted_arr.begin(), stl_sorted_arr.end());
	
	TEST_TYPE(" : Quick Sort\n");
	SortingNLogN::quickSort(arr.data(), arr.size());
	if (stl_sorted_arr.size() == arr.size() && stl_sorted_arr == arr)
	{
		TEST_PASS;
	}
	else
	{
		TEST_FAIL;
		ASSERT;
		return;
	}
	testNum++;

	TEST_TYPE(" : Merge Sort 1\n");
	arr = dataVec;
	SortingNLogN::mergeSort_1(arr.data(), arr.size());
	if (stl_sorted_arr.size() == arr.size() && stl_sorted_arr == arr)
	{
		TEST_PASS;
	}
	else
	{
		TEST_FAIL;
		ASSERT;
		return;
	}
	testNum++;

	TEST_TYPE(" : Merge Sort 2\n");
	arr = dataVec;
	SortingNLogN::mergeSort_2(arr.data(), arr.size());
	if (stl_sorted_arr.size() == arr.size() && stl_sorted_arr == arr)
	{
		TEST_PASS;
	}
	else
	{
		TEST_FAIL;
		ASSERT;
		return;
	}
	testNum++;

	TEST_TYPE(" : Heap Sort\n");
	arr = dataVec;
	SortingNLogN::heapSort(arr.data(), arr.size());
	if (stl_sorted_arr.size() == arr.size() && stl_sorted_arr == arr)
	{
		TEST_PASS;
	}
	else
	{
		TEST_FAIL;
		ASSERT;
		return;
	}
	testNum++;
}

void test_SortingNLogN()
{
	LOG_ENTRY;
	test_SortingNLogN_1();
	LOG_EXIT;
	ns_Util::Logger::LOG_MSG("#####################################\n");
}

}	// namespace nsCpp_DS

#endif //#ifndef __SORTING_N_LOG_N_H__
#ifndef __MULTITHREAD_ACCUMULATE_H__
#define __MULTITHREAD_ACCUMULATE_H__

#include <vector>
#include <iostream>
#include <thread>
#include <numeric>
#include <algorithm>
#include "helper.h"

namespace nsCppThreads
{
class MultithreadAccumulate
{
public:
	MultithreadAccumulate() = default;

	void test()
	{
		std::cout << "Testing : Using multithreaded accumulate on very large vector.\n\n";
		testAccumulate_parallel();
		std::cout << "\n\n\n";
	}
private:
	template <typename Iterator, typename T>
	void accumulateBlock(Iterator first, Iterator last, T &sum)
	{
		sum = std::accumulate(first, last, sum);
	}

	template <typename Iterator, typename T>
	T accumulate_parallel(Iterator first, Iterator last, T initVal)
	{
		size_t length = std::distance(first, last);
		if (!length)
		{
			return initVal;
		}

		int min_per_thread = 25;

		size_t max_threads = (length + min_per_thread - 1) / min_per_thread;
		size_t hw_concurrency = std::thread::hardware_concurrency();

		size_t num_threads = std::min(hw_concurrency != 0 ? hw_concurrency : 2, max_threads);

		size_t block_len = length / num_threads;

		std::cout << "max_threads = " << max_threads << '\n';
		std::cout << "hw_concurrency = " << hw_concurrency << '\n';
		std::cout << "num_threads = " << num_threads << '\n';
		std::cout << "block_len = " << block_len << "\n\n";

		std::vector<T> results(num_threads);
		std::vector<std::thread> threads(num_threads - 1);

		Iterator block_start = first;
	
		for (size_t i = 0; i < (num_threads - 1); ++i)
		{
			Iterator block_end = block_start;
			std::advance(block_end, block_len);
			threads[i] = std::thread(&MultithreadAccumulate::accumulateBlock<Iterator, T>, this, block_start, block_end, std::ref(results[i]));
			block_start = block_end;
		}

		accumulateBlock( block_start, last, results[num_threads - 1]);

		// join all thread
		std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

		return accumulate(results.begin(), results.end(), initVal);
	}

	void testAccumulate_parallel()
	{
		std::vector<int> vec;
		size_t maxVal = vec.max_size();
		vec.resize(maxVal/1000000000);

		Timer timer;
		std::iota(vec.begin(), vec.end(), 1);
		timer.print("To fill the vec of size " + std::to_string(vec.size()) + " it took ");

		timer.start();
		size_t res = accumulate_parallel(vec.begin(), vec.end(), 1);
		timer.print("To accumulate with threads it took ");
		
		timer.start();
		res = accumulate(vec.begin(), vec.end(), 1);
		timer.print("To accumulate without threads it took ");
	}
};
}
#endif	//__MULTITHREAD_ACCUMULATE_H__
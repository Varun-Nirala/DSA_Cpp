#ifndef __THREAD_1_H__
#define __THREAD_1_H__

#include <iostream>
#include <thread>
#include <mutex>

namespace nsCppThreads
{
class Thread_1
{
	const size_t		m_maxThreads{};
	std::mutex			g_mutex{};

	void threadFun(size_t id)
	{
		std::lock_guard<std::mutex> lg(g_mutex);

		std::cout << "I am thread number :: " << id << "\n";
		std::cout << "My unique id is :: " << std::this_thread::get_id() << "\n";
	}

public:
	Thread_1()
		:m_maxThreads{ std::thread::hardware_concurrency() * 2 }
	{}

	void test()
	{
		std::cout << "Testing : Normal thread creation and function execution using mutex.\n\n";
		std::thread* threadArr = nullptr;
		threadArr = new std::thread[m_maxThreads];

		std::cout << "Main thread's id is " << std::this_thread::get_id() << '\n';

		for (size_t i = 0; i < m_maxThreads; ++i)
		{
			threadArr[i] = std::thread(&Thread_1::threadFun, this, i);
		}

		for (size_t i = 0; i < m_maxThreads; ++i)
		{
			threadArr[i].join();
		}
		delete[]threadArr;
		std::cout << "\n\n\n";
	}
};
}
#endif	//#ifndef __THREAD_1_H__
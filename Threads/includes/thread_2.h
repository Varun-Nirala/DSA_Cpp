#ifndef __THREAD_2_H__
#define __THREAD_2_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

namespace nsCppThreads
{
class Thread_2
{
	const size_t		m_maxThreads{};
	std::mutex			g_mutex{};

	void threadFunc(size_t id)
	{
		std::lock_guard<std::mutex> lg(g_mutex);
		std::cout << "threadFunc(): my arg is : " << id << '\n';
	}

	void bindFunc(size_t id, std::string msg)
	{
		std::lock_guard<std::mutex> lg(g_mutex);
		std::cout << "bindFunc(): my arg are : id " << id << ", msg = " << msg << '\n';
	}

public:
	Thread_2()
		:m_maxThreads{ std::thread::hardware_concurrency() }
	{}

	void test()
	{
		std::cout << "Testing : Normal thread creation with bind for params function execution using mutex.\n\n";
		std::vector<std::thread> v_thread;
		v_thread.reserve(m_maxThreads);

		size_t i = 0;
		for (i = 0; i < m_maxThreads / 2; ++i)
		{
			v_thread.emplace_back(std::thread(&Thread_2::threadFunc, this, i));
		}

		// void (*funcPtr)(int i, string) = &bindFunc;	// functiom pointer example

		std::function<void(std::string, size_t)> func = std::bind(&Thread_2::bindFunc, this, std::placeholders::_2, std::placeholders::_1);

		for (i; i < m_maxThreads; ++i)
		{
			std::string msg{ "I am number " + std::to_string(i) };
			v_thread.push_back(std::move(std::thread(func, msg, i)));
		}

		std::for_each(v_thread.begin(), v_thread.end(), std::mem_fn(&std::thread::join));
		std::cout << "\n\n\n";
	}
};
}
#endif	//#ifndef __THREAD_2_H__
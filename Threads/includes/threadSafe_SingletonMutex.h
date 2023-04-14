#ifndef __THREAD_SAFE_SINGLETON_MUTEX_H__
#define __THREAD_SAFE_SINGLETON_MUTEX_H__
/*
thread safe singleton
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <functional>
#include <memory>
#include <algorithm>

namespace nsCppThreads
{
class SingletonUsingMutex
{
public:
	virtual ~SingletonUsingMutex() = default;

	static SingletonUsingMutex& getInstance()
	{
		if (!m_pInstance)
		{
			std::lock_guard<std::mutex> lg(m_mutex);
			if (!m_pInstance)
			{
				m_pInstance.reset(new SingletonUsingMutex());
			}
		}
		return *m_pInstance.get();
	}

private:
	SingletonUsingMutex() = default;
	SingletonUsingMutex(SingletonUsingMutex &) = delete;
	SingletonUsingMutex& operator=(const SingletonUsingMutex &) = delete;

	static std::unique_ptr<SingletonUsingMutex>		m_pInstance;
	static std::mutex								m_mutex;
};

std::unique_ptr<SingletonUsingMutex> SingletonUsingMutex::m_pInstance;
std::mutex SingletonUsingMutex::m_mutex;

class ThreadSafeSingletonMutex
{
public:
	ThreadSafeSingletonMutex() = default;

	void test()
	{
		std::cout << "Testing : Singleton with using mutex.\n\n";
		std::vector<std::thread> v_thread;

		v_thread.reserve(m_maxThreads);

		for (int i = 0; i < m_maxThreads; ++i)
		{
			v_thread.push_back(std::move(std::thread(&SingletonUsingMutex::getInstance)));
		}
		for_each(v_thread.begin(), v_thread.end(), std::mem_fn(&std::thread::join));
		std::cout << "\n\n\n";
	}
private:
	const int		m_maxThreads{ 20 };
};
}
#endif //#ifndef __THREAD_SAFE_SINGLETON_MUTEX_H__
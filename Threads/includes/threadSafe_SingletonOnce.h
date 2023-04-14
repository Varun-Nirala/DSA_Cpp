#ifndef __THREAD_SAFE_SINGLETON_ONCE_H__
#define __THREAD_SAFE_SINGLETON_ONCE_H__
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
class SingletonUsingOnce
{
public:
	virtual ~SingletonUsingOnce() = default;

	static SingletonUsingOnce& getInstance()
	{
		std::call_once(m_OnceFlag, [](){ m_pInstance.reset(new SingletonUsingOnce()); });
		return *m_pInstance.get();
	}

private:
	SingletonUsingOnce() = default;
	SingletonUsingOnce(SingletonUsingOnce &) = delete;
	SingletonUsingOnce& operator=(const SingletonUsingOnce &) = delete;

	static std::unique_ptr<SingletonUsingOnce>		m_pInstance;
	static std::once_flag							m_OnceFlag;
};
std::unique_ptr<SingletonUsingOnce> SingletonUsingOnce::m_pInstance;
std::once_flag SingletonUsingOnce::m_OnceFlag;


class ThreadSafeSingletonOnce
{
public:
	ThreadSafeSingletonOnce() = default;
	void test()
	{
		std::cout << "Testing : Singleton with using once_flag.\n\n";
		std::vector<std::thread> v_thread;

		v_thread.reserve(m_maxThreads);

		for (int i = 0; i < m_maxThreads; ++i)
		{
			v_thread.push_back(std::move(std::thread(&SingletonUsingOnce::getInstance)));
		}
		for_each(v_thread.begin(), v_thread.end(), std::mem_fn(&std::thread::join));
		std::cout << "\n\n\n";
	}
private:
	const int		m_maxThreads{20};
};
}
#endif //#ifndef __THREAD_SAFE_SINGLETON_MUTEX_H__
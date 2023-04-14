#ifndef __THREAD_4_H__
#define __THREAD_4_H__

#include <iostream>
#include <thread>
#include <string>

namespace nsCppThreads
{
class Thread_4
{
public:
	void test()
	{
		int add = 4;
		int mult = 5;
		std::thread::id this_id = std::this_thread::get_id();

		std::cout << "Main thread id = " << this_id << '\n';

		std::thread t_thread1(&Thread_4::function_add, this, add);
		std::thread t_thread2(&Thread_4::function_mult, this, mult);

		t_thread1.join();
		t_thread2.join();
	}
private:
	void function_add(int number)
	{
		m_mutex.lock();
		std::thread::id this_id = std::this_thread::get_id();
		std::cout << __func__ << " is called, with thread id = " << this_id << '\n';
		m_mutex.unlock();

		for(int i = 0; i < number; i++)
		{
			m_mutex.lock();
			std::cout << __func__ << " : " << i << " + " << number << " = " << i + number << '\n';
			m_mutex.unlock();
		}
		std::cout << "Exiting.\n";
	}

	void function_mult(int number)
	{
		m_mutex.lock();
		std::thread::id this_id = std::this_thread::get_id();
		std::cout << __func__ << " is called, with thread id = " << this_id << '\n';
		m_mutex.unlock();

		for (int i = 0; i < number; i++)
		{
			m_mutex.lock();
			std::cout << __func__ << " : " << i << " * " << number << " = " << i * number << '\n';
			m_mutex.unlock();
		}
		std::cout << "Exiting.\n";
	}
private:
	std::mutex		m_mutex;
};
}
#endif //#ifndef __THREAD_4_H__
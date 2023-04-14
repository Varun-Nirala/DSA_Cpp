#ifndef __THREAD_3_H__
#define __THREAD_3_H__

#include <iostream>
#include <thread>

namespace nsCppThreads
{
class Counter
{
public:
	Counter(int id, int numIterations)
		: m_id(id)
		, m_numIterations(numIterations)
	{}

	inline void operator() () const { process(); }

	inline void process() const
	{
		for (size_t i = 0; i < m_numIterations; ++i)
		{
			std::cout << "Counter " << m_id << " has value ";
			std::cout << i << '\n';
		}
	}

private:
	int		m_id{};
	int		m_numIterations{};
};

class Thread_3
{
public:
	void test()
	{
		std::cout << "Testing : Different initialization, exception handling and use of atomic.\n\n";
		example_1();
		example_2();
		example_3<int>();
		std::cout << "\n\n\n";
	}
private:
/************************ Example 1 START ************************/
	void counterFunc(int id, int numIterations)
	{
		for (int i = 0; i < numIterations; ++i)
		{
			std::cout << "Counter " << id << " has value ";
			std::cout << i << '\n';
		}
	}

	// Different way of initializing thread
	void example_1()
	{
		std::cout << "Running example_1, showing different type of initializations.\n";
		std::vector<std::thread> threads;
		threads.emplace_back(std::thread(&Thread_3::counterFunc, this, 1, 4));
		threads.emplace_back(std::thread(&Thread_3::counterFunc, this, 2, 6));

		// Using uniform initialization
		threads.emplace_back(std::thread{ Counter{3, 20} });
		threads.emplace_back(std::thread( Counter(4, 10) ));

		Counter count(5, 20);
		threads.emplace_back(std::thread(&Counter::process, &count));

		int id = 6;
		int numIterations = 5;
		threads.emplace_back(std::thread([id, numIterations] {
			for (int i = 0; i < numIterations; ++i)
			{
				std::cout << "Counter " << id << " has value ";
				std::cout << i << '\n';
			}
		}));

		for (auto& t : threads)
		{
			t.join();
		}
	}
	/************************ Example 1 END ************************/



	/************************ Example 2 START ************************/
	// exception handling in threads, passing exception from one thread to another thread
	// Every thread can throw its own exceptions, but they need t be caught within their own thread.
	// Exception thrown in one thread cannot be caught in another thread

	void doSomeWork()
	{
		for (int i = 0; i < 5; ++i)
		{
			std::cout << i << '\n';
		}
		std::cout << "Thread throwing a runtine_error exception...\n";
		throw std::runtime_error("Exception from thread");
	}

	void threadFunc(std::exception_ptr &error)
	{
		try
		{
			doSomeWork();
		}
		catch (...)
		{
			std::cout << "Thread caught exception, returning exception...\n";
			error = std::current_exception();
		}
	}

	void doWorkInThread()
	{
		std::exception_ptr error;
		std::thread t(&Thread_3::threadFunc, this, ref(error));

		t.join();

		if (error)
		{
			std::cout << "Main thread received exception, rethrowing it...\n";
			std::rethrow_exception(error);
		}
		else
		{
			std::cout << "Main thread did not received any exception.\n";
		}
	}

	void example_2()
	{
		std::cout << "Running example_2, showing exception in thread and rethrow.\n";
		try
		{
			doWorkInThread();
		}
		catch (const std::exception &e)
		{
			std::cout << "Main function caught: '" << e.what() << "'\n";
		}
	}
	/************************ Example 2 END ************************/



	/************************ Example 3 START ************************/
	// Use of atomic class for creating variable which is thread-safe and race condition free
	template <typename T>
	void func(T &inCounter)
	{
		for (int i = 0; i < 100; ++i)
		{
			++inCounter;
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	template<typename T>
	void example_3()
	{
		std::cout << "Running example_3, showing use of atomic.\n";
		T counter = 0;
		vector<std::thread> threads;

		for (int i = 0; i < 10; ++i)
		{
			threads.push_back(std::thread(&Thread_3::func<T>, this, std::ref(counter)));
		}

		for (auto &t : threads)
		{
			t.join();
		}

		if (std::is_same<T, std::atomic_int>::value)
		{
			std::cout << "Result Example 3 with atomic counter = " << counter << '\n';
		}
		else
		{
			std::cout << "Result Example 3 without atomic counter = " << counter << '\n';
		}
	}
	/************************ Example 3 END ************************/
};
}
#endif //#ifndef __THREAD_3_H__
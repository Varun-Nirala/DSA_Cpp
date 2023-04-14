#ifndef __THREAD_SAFE_PRODUCER_CONSUMER_H__
#define __THREAD_SAFE_PRODUCER_CONSUMER_H__

/*
thread safe queue, example of producer consumer problem
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace nsCppThreads
{
template<typename T>
class threadSafe_queue
{
public:
	threadSafe_queue(){};
	threadSafe_queue(const threadSafe_queue&other)
	{
		lock_guard<mutex> lg(m_mutex);
		m_queue = other.m_queue;
	}
	threadSafe_queue& operator=(const threadSafe_queue &) = delete;

	void push(T new_value)
	{
		std::lock_guard<std::mutex>	lg(m_mutex);
		m_queue.push(new_value);
		m_cv.notify_one();
	}

	bool try_pop(T& value)
	{
		std::lock_guard<std::mutex> lg(m_mutex);
		if (m_queue.empty())
		{
			return false;
		}
		value = m_queue.front();
		m_queue.pop();
		return true;
	}

	std::shared_ptr<T> try_pop()
	{
		std::lock_guard<std::mutex> m_mutex;
		if (m_queue.empty())
		{
			return std::shared_ptr<T>();
		}
		std::shared_ptr<T> res(std::make_shared<T>(m_queue.front()));
		return res;
	}

	void wait_and_pop(T &value)
	{
		std::unique_lock<std::mutex>	ul(m_mutex);
		m_cv.wait(ul, [this](){ return !m_queue.empty(); });
		value = m_queue.front();
		m_queue.pop();
	}

	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_lock<std::mutex>	ul(m_mutex);
		m_cv.wait(ul, [this](){ return !m_queue.empty(); });
		std::shared_ptr<T> res(std::make_shared<T>(m_queue.front()));
		m_queue.pop();
		return res;
	}

	bool empty() const
	{
		std::lock_guard<std::mutex>	lg(m_mutex);
		return m_queue.empty();
	}

private:
	mutable std::mutex			m_mutex;
	std::queue<T>				m_queue;
	std::condition_variable		m_cv;
};

/* PRODUCER CONSUMER EXAMPLE */
class ProducerConsumer
{
private:
	bool more_data_to_prepare()
	{
		static int count = 0;
		return count++ < m_maxRun;
	}

	inline int prepare_data() { return rand() % 100; }

	void producer()
	{
		while (more_data_to_prepare())
		{
			int data = prepare_data();
			std::cout << "Prepared data is : " << data << "\n";
			g_myQueue.push(data);
		}
		m_bProducerDone = true;
	}

	inline void process(int data) const { std::cout << "Data to be processed is : " << data << "\n"; }

	inline bool is_last_chunk(int data) { return m_bProducerDone && g_myQueue.empty(); }

	void consumer() 
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			int data = -1;
			g_myQueue.wait_and_pop(data);
			process(data);
			if (is_last_chunk(data))
				break;
		}
	}
public:
	void test()
	{
		std::cout << "Testing : Producer & Consumer with maxRun = " << m_maxRun << "\n\n";
		
		std::thread producerT(&ProducerConsumer::producer, this);
		std::thread consumerT(&ProducerConsumer::consumer, this);

		producerT.join();
		consumerT.join();
		std::cout << "\n\n\n";
	}

private:
	bool					m_bProducerDone{ false };
	const int				m_maxRun{ 20 };
	threadSafe_queue<int>	g_myQueue;
};

}
#endif //#ifndef __THREAD_SAFE_PRODUCER_CONSUMER_H__
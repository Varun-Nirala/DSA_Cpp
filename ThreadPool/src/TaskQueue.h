/*
	@ref	:	From book Concurrency in Cpp
	@desc	:	Thread safe queue, which gonna hold the task(can hold anything though)
				to be executed by threads in ThreadPool class.
*/
#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

namespace nsThreadPool
{
	template<typename T>
	class TS_Queue
	{
		public:
			// ctor
			TS_Queue() = default;
			TS_Queue(const TS_Queue &rhs);
			TS_Queue(const TS_Queue &&rhs);

			// assignment operator
			TS_Queue& operator=(const TS_Queue &rhs);

			// interface
			bool push(T value);
			
			void wait_and_pop(T &popedValue);
			std::shared_ptr<T> wait_and_pop();

			bool try_and_pop(T &popedValue);
			std::shared_ptr<T> try_and_pop();

			bool empty();

		private:
			std::queue<T>				m_queue;
			std::mutex					m_mutex;
			std::condition_variable		m_cv;
	};

	template<typename T>
	TS_Queue<T>::TS_Queue(const TS_Queue &rhs)
	{
		std::lock_guard<std::mutex>	lg(m_mutex);
		this->m_queue = rhs.m_queue;
	}

	template<typename T>
	TS_Queue<T>::TS_Queue(const TS_Queue &&rhs)
	{
		std::lock_guard<std::mutex>	lg(m_mutex);

		m_queue(std::move(rhs.m_queue));
		while (!rhs.m_queue.empty())
		{
			rhs.m_queue.pop();
		}
	}

	template<typename T>
	TS_Queue<T>& TS_Queue<T>::operator=(const TS_Queue &rhs)
	{
		std::lock_guard<std::mutex>	lg(m_mutex);
		if (this == &rhs)
		{
			return *this;
		}

		m_queue = rhs.m_queue;
		while (!rhs.m_queue.empty())
		{
			rhs.m_queue.pop();
		}
	}

	template<typename T>
	bool TS_Queue<T>::push(T value)
	{
		std::lock_guard<std::mutex> lg(m_mutex);
		m_queue.push(value);
		m_cv.notify_one();
		return true;
	}

	template<typename T>
	void TS_Queue<T>::wait_and_pop(T &popedValue)
	{
		std::lock_guard<std::mutex>	lg(m_mutex);
		m_cv.wait(lg, [](){ return !m_queue.empty(); });
		popedValue = m_queue.front();
		m_queue.pop();
	}

	template<typename T>
	std::shared_ptr<T> TS_Queue<T>::wait_and_pop()
	{
		std::unique_lock<std::mutex> ug(m_mutex);
		m_cv.wait(ug, [this](){ return !m_queue.empty(); });
		std::shared_ptr<T> res(std::make_shared<T>(m_queue.front()));
		m_queue.pop();
		return res;
	}

	template<typename T>
	bool TS_Queue<T>::try_and_pop(T &popedValue)
	{
		std::lock_guard<std::mutex>	lg(m_mutex);
		if (m_queue.empty())
		{
			return false;
		}
		popedValue = m_queue.front();
		m_queue.pop();
		return true;
	}

	template<typename T>
	std::shared_ptr<T> TS_Queue<T>::try_and_pop()
	{
		std::lock_guard<std::mutex>	lg(m_mutex);

		if (m_queue.empty())
		{
			return std::shared_ptr<T>();
		}
		std::shared_ptr<T> res(std::make_shared<T>(m_queue.front()));
		m_queue.pop();
		return true;
	}

	template<typename T>
	bool TS_Queue<T>::empty()
	{
		std::lock_guard<mutex>	lg(m_mutex);
		return m_queue.empty();
	}
}
#endif //#ifndef __TASKQUEUE_H__
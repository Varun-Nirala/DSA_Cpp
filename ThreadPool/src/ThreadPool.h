#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__
#include <vector>
#include <thread>
#include <future>

namespace nsThreadPool
{
	namespace nsConstant
	{
		const int MAX_THREAD = 25;
	}

	class ThreadPool
	{
			/* DELETED functions, non moveable, copyable, assignable */
			ThreadPool(ThreadPool &) = delete;
			ThreadPool(ThreadPool &&) = delete;
			ThreadPool& operator=(ThreadPool &) = delete;

		public:
			ThreadPool(int nThread = nsConstant::MAX_THREAD);

		private:
			std::vector<std::thread>	m_threadVec;
	};
}
#endif	//#ifndef __THREADPOOL_H__
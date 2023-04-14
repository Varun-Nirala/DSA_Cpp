#ifndef __MYTASK_H__
#define __MYTASK_H__

#include <iostream>
#include <string>
#include <thread>
#include "Callable.h"

namespace nsThreadPool
{
	class PrintMsg : public Callable
	{
		public:
			PrintMsg(const std::string &msg, int times = 10, int sleepFor = 1)
				: m_times(times)
				, m_sleepFor(sleepFor)
				, m_sMsg(msg)
			{}

			virtual void operator()()
			{
				for (int i = 0; i < m_times; ++i)
				{
					std::cout << m_sMsg << "\n";
					std::this_thread::sleep_for(std::chrono::milliseconds(m_sleepFor));
				}
			}

		private:
			int				m_times;
			int				m_sleepFor;
			std::string		m_sMsg;
	};
}
#endif //#ifndef __MYTASK_H__
#include "ThreadPool.h"

using namespace nsThreadPool;
using namespace std;

ThreadPool::ThreadPool(int nThread)
{
	m_threadVec.reserve(nThread);
	for (int i = 0; i < nThread; ++i)
	{
		m_threadVec.push_back(thread());
	}
}
#include <iostream>
#include "thread_1.h"
#include "thread_2.h"
#include "thread_3.h"
#include "thread_4.h"
#include "Async_1.h"
#include "multithreadAccumulate.h"
#include "threadSafe_SingletonMutex.h"
#include "threadSafe_SingletonOnce.h"
#include "theadSafe_ProducerConsumer.h"

using namespace std;

int main()
{
	nsCppThreads::Thread_1 t1;
	nsCppThreads::Thread_2 t2;
	nsCppThreads::Thread_3 t3;
	nsCppThreads::Thread_4 t4;

	nsCppThreads::MultithreadAccumulate m1;
	nsCppThreads::Async_1 a1;

	nsCppThreads::ThreadSafeSingletonMutex s1;
	nsCppThreads::ThreadSafeSingletonOnce s2;
	nsCppThreads::ProducerConsumer p1;

	t1.test();
	t2.test();
	t3.test();
	t4.test();
	a1.test();
	
	m1.test();

	s1.test();
	s2.test();
	p1.test();
	return 0;
}
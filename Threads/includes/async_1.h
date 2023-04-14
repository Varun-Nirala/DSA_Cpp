#ifndef __ASYNC_1_H__
#define __ASYNC_1_H__

#include <iostream>
#include <thread>
#include <future>
#include <string>

namespace nsCppThreads
{
class MyFunctor
{
public:
	void operator()(const std::string &msg) { std::cout << "Received msg is : " << msg << "\n"; }

	std::string toUpper(std::string msg)
	{
		std::string ans;
		std::transform(msg.begin(), msg.end(), std::back_inserter(ans), std::toupper);
		return ans;
	}
};

class Async_1
{
public:
	Async_1() = default;

	void test()
	{
		std::cout << "Testing : Using Async.\n\n";
		test_1();
		test_2();
		std::cout << "\n\n\n";
	}

private:
	int findTheAnswer()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		return 50;
	}

	void test_1()
	{
		std::cout << "Starting new thread.\n";
		std::future<int> f_answer = std::async(std::launch::async, &Async_1::findTheAnswer, this);
		std::cout << "Going into hybernation.\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << "Awaked from slumber.\n";

		std::cout << "The answer i got is : " << f_answer.get() << '\n';
	}

	void test_2()
	{
		MyFunctor myF;
		std::future<void> f_operator = std::async(std::launch::deferred, std::ref(myF), "Hello");

		std::future<std::string> f_toUpper = std::async(std::launch::async, &MyFunctor::toUpper, &myF, "I am varun.");

		f_operator.get();

		std::string ans = f_toUpper.get();

		std::cout << "Received answer is :: " << ans << '\n';
	}
};
}
#endif //#ifndef __ASYNC_1_H__
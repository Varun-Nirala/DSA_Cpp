#pragma once

#include <mutex>

class Singleton
{
public:
	static Singleton& getInstance()
	{
		static Singleton m_instance;
		return m_instance;
	}

	void doWork()
	{
		std::cout << "Singleton:: Doing work\n";
	}
private:
	Singleton() = default;
	~Singleton() = default;

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};

class Singleton1
{
public:
	static Singleton1& getInstance()
	{
		std::call_once(m_onceFlag, &Singleton1::initSingleton1);
		return *m_pInstance;
	}

	void doWork()
	{
		std::cout << "Singleton1:: Doing work\n";
	}
private:
	Singleton1() = default;
	~Singleton1() = default;

	Singleton1(const Singleton1&) = delete;
	Singleton1& operator=(const Singleton1&) = delete;

	static void initSingleton1()
	{
		m_pInstance = new Singleton1();
	}

	static Singleton1* m_pInstance;
	static std::once_flag m_onceFlag;
};

Singleton1* Singleton1::m_pInstance{};
std::once_flag Singleton1::m_onceFlag;
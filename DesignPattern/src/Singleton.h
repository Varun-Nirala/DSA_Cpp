#pragma once

#include <iostream>

class Singleton final
{
public:
	static Singleton& getInstance()
	{
		static Singleton *m_pInstance = new Singleton(); 
		return *m_pInstance;
	}

	void doWork()
	{
		std::cout << "I am Singleton\n";
	}

	Singleton(const Singleton &) = delete;
	Singleton(Singleton &&) = delete;

	Singleton& operator=(const Singleton &) = delete;
	Singleton& operator=(Singleton &&) = delete;

	~Singleton()
	{
		std::cout << "Dtor : I am Done\n";
	}
private:
	Singleton()
	{
		std::cout << "Ctor : I am Alive\n";
	}
};
#include <iostream>

#include "Singleton.h"

using namespace std;
int main()
{
	Singleton::getInstance().doWork();
	return 0;
}
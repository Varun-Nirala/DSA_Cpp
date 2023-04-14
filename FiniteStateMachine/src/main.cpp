#include <iostream>
#include <string>

#include "StateMachine.h"

using namespace std;

void FirstOnEnter();
void FirstOnExit();
void SecondOnEnter();
void SecondOnExit();
void ThirdOnEnter();
void ThirdOnExit();

int main(int argc, char *argv[])
{
	StateMachine stateMachine;

	stateMachine.insert("First", FirstOnEnter);
	stateMachine.insert("Second", SecondOnEnter, SecondOnExit);
	stateMachine.insert("Third", FirstOnEnter);

	int numberOfState = 4;

	for(int i = 0; i < numberOfState; ++i)
	{
		stateMachine.nextState();
	}

	return 0;
}

void FirstOnEnter()
{
	cout << __func__ << "::Called";
}

void FirstOnExit()
{
	cout << __func__ << "::Called";
}

void SecondOnEnter()
{
	cout << __func__ << "::Called";
}

void SecondOnExit()
{
	cout << __func__ << "::Called";
}

void ThirdOnEnter()
{
	cout << __func__ << "::Called";
}

void ThirdOnExit()
{
	cout << __func__ << "::Called";
}